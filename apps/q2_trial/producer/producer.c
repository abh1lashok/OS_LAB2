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
  
  Circular_Buffer* cb;
  lock_t lock;
  // lock_t prod_cons_lock;


  sem_t full_sem;
  sem_t empty_sem;

  int j;
  char DATA[] = "0123456789";
  //Printf("DATA[11] = %d\n",DATA[11]);
  if (argc != 6) { 
    Printf("Usage: "); Printf(argv[0]); Printf(" <handle_to_shared_memory_page> <handle_to_page_mapped_semaphore> <handle to lock>\n"); 
    Exit();
  } 

  // Convert the command-line strings into integers for use as handles
  h_mem = dstrtol(argv[1], NULL, 10); // The "10" means base 10
  s_procs_completed = dstrtol(argv[2], NULL, 10);
  lock = dstrtol(argv[3], NULL, 10);
  full_sem = dstrtol(argv[4], NULL, 10);
  empty_sem = dstrtol(argv[5], NULL, 10);


  // Printf(" Producer Consumer LOck For PROD ---PID %d = %d \n",Getpid(),prod_cons_lock);

  // Map shared memory page into this process's memory space
  if ((mc = (missile_code *)shmat(h_mem)) == NULL) {
    Printf("Could not map the virtual address to the memory in "); Printf(argv[0]); Printf(", exiting...\n");
    Exit();
  }
 
  // Now print a message to show that everything worked
  
  // Printf("-------------\nPROD - PID %d: This is one of the %d instances you created.\n-------------\n",Getpid(), mc->numprocs);
  // Printf("spawn_me - %d: Missile code is: %c\n",Getpid(), mc->really_important_char);
  // Printf("spawn_me - %d: Missile code cb.head is: %d\n",Getpid(), mc->cb.head);
  // Printf("spawn_me - %d: Missile code cb.tail is: %d\n",Getpid(), mc->cb.tail);
  // Printf("spawn_me - %d: Missile code cb.buffer is: %d\n",Getpid(), mc->cb.buffer[0]);
  // Printf("spawn_me: My PID is %d\n", Getpid());

  cb  = &(mc->cb);
  j = 0;

  // Printf("PROD - PID %d: Putting Data in\n");
  while((DATA[j-1] != '\0') || j == 0){
    
    if(sem_wait(empty_sem)) Printf("PROD - PID %d ---- Succesful Wait for j =  %d \n",Getpid(),j);
    //get lock
    if(lock_acquire(lock))Printf("\nPROD - PID %d ---- ACQUIRED LOCK \n",Getpid());;
    // lock_acquire(prod_cons_lock);
    
      
      Printf("PROD - PID %d ---- Put %c in cb \n",Getpid(),DATA[j]);
      put_item_cb(DATA[j],cb);
      j++;
      
    
      Printf("\n");
    // lock_release(prod_cons_lock);
    
    // sem_signal(full_sem);
    // Printf("PROD - PID %d ----",Getpid());
    // Print_cb(cb);
    // sem_signal(full_sem);
    
    if(sem_signal(full_sem))Printf("PROD - PID %d ---- Successful Signal For j =  %d \n",Getpid(),j-1);
    if(lock_release(lock))Printf("\nPROD - PID %d ---- RELEASED LOCK \n",Getpid());
    // lock_release(lock);
    


  }

  lock_acquire(lock);
  Printf("PROD - PID ---- %d Sent Everything \n",Getpid());
  lock_release(lock);


  // Printf("cb - %d ---- %p \n",Getpid(),cb);


  // Signal the semaphore to tell the original process that we're done
  Printf("PROD - PID %d is complete.\n", Getpid());
  if(sem_signal(s_procs_completed) != SYNC_SUCCESS) {
    Printf("Bad semaphore s_procs_completed (%d) in ", s_procs_completed); Printf(argv[0]); Printf(", exiting...\n");
    Exit();
  }
}
