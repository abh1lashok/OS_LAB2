#include "lab2-api.h"
#include "usertraps.h"
#include "misc.h"

#include "spawn.h"

#ifndef __CB__
#define __CB__
#include "CircularBuffer.h"
#endif

// void put_data(Circular_Buffer* cb){
  

  
  



// }
void main (int argc, char *argv[])
{
  missile_code *mc;        // Used to access missile codes in shared memory page
  uint32 h_mem;            // Handle to the shared memory page
  sem_t s_procs_completed; // Semaphore to signal the original process that we're done
  lock_t lock;
  lock_t prod_cons_lock;
  Circular_Buffer* cb;
  int i;
  int j;
  char DATA[1000];
  j = 0;
  if (argc != 5) { 
    Printf("Usage: "); Printf(argv[0]); Printf(" <handle_to_shared_memory_page> <handle_to_page_mapped_semaphore> <handle to lock>\n"); 
    Exit();
  } 

  // Convert the command-line strings into integers for use as handles
  h_mem = dstrtol(argv[1], NULL, 10); // The "10" means base 10
  s_procs_completed = dstrtol(argv[2], NULL, 10);
  lock = dstrtol(argv[3], NULL, 10);
  prod_cons_lock = dstrtol(argv[4], NULL, 10);
  Printf(" Producer Consumer LOck For CONS ---PID %d = %d \n",Getpid(),prod_cons_lock);
  // Map shared memory page into this process's memory space
  if ((mc = (missile_code *)shmat(h_mem)) == NULL) {
    Printf("Could not map the virtual address to the memory in "); Printf(argv[0]); Printf(", exiting...\n");
    Exit();
  }
 
  // Now print a message to show that everything worked
  Printf("CONS - %d: This is one of the %d instances you created.  ",Getpid(), mc->numprocs);
  // Printf("spawn_me - %d: Missile code is: %c\n",Getpid(), mc->really_important_char);
  // Printf("spawn_me - %d: Missile code cb.head is: %d\n",Getpid(), mc->cb.head);
  // Printf("spawn_me - %d: Missile code cb.tail is: %d\n",Getpid(), mc->cb.tail);
  // Printf("spawn_me - %d: Missile code cb.buffer is: %d\n",Getpid(), mc->cb.buffer[0]);
  // Printf("spawn_me: My PID is %d\n", Getpid());

  cb  = &(mc->cb);

  // Printf("spawn_me - %d: Putting Data in\n");
  while((isxdigit(DATA[j-1]))  || j == 0){
    
    //get lock
    lock_acquire(lock);
    // lock_acquire(prod_cons_lock);
    if(!is_empty(cb)){

      check_item_cb(&DATA[j],cb); //copyin gof data happening here to DATA[1000] from cb
      if (((j == 0)&&(DATA[j] == '0'))||
          ((j != 0)&&((DATA[j] == DATA[j-1] + 1)||(!isxdigit(DATA[j]))))){     //(!isxdigit(DATA[J])) it will terminate the conusmer gracefully)
                  get_item_cb(&DATA[j],cb);
                  Printf("CONS - PID %d ---- Got %c from cb \n",Getpid(),DATA[j]);
                  j++;

          }
      else Printf("CONS - PID %d ---- Tried to Pick Wrong Data \n",Getpid());

      
      

      
    }
    else {
      Printf("CONS - PID %d ---- Buffer is Empty \n",Getpid());
      
    }
    Printf("\n");
    // lock_release(prod_cons_lock);
    lock_release(lock);
    


  }

lock_acquire(lock);
  Printf("CONS - PID %d ---- Finally Got : ",Getpid());
  for(i = 0; i < C_BUFFER_SIZE; i++){
    Printf("%c",DATA[i]);
  }
  Printf("\n");
  Printf("CONS - PID %d is complete.\n", Getpid());
lock_release(lock);



  // Printf("cb - %d ---- %p \n",Getpid(),cb);


  // Signal the semaphore to tell the original process that we're done
  
  if(sem_signal(s_procs_completed) != SYNC_SUCCESS) {
    Printf("Bad semaphore s_procs_completed (%d) in ", s_procs_completed); Printf(argv[0]); Printf(", exiting...\n");
    Exit();
  }
}
