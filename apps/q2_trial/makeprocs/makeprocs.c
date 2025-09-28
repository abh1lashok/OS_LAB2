#include "lab2-api.h"
#include "usertraps.h"
#include "misc.h"



#include "spawn.h"
// #include "CircularBuffer.h"
#ifndef __CB__
#define __CB__
#include "CircularBuffer.h"
#endif


#define NO_OF_PROCESSES 3
#define NO_OF_PRODUCERS NO_OF_PROCESSES
#define NO_OF_CONSUMERS NO_OF_PROCESSES






void main (int argc, char *argv[])
{
  int numprocs = 0;               // Used to store number of processes to create
  int i;                          // Loop index variable
  missile_code *mc;               // Used to get address of shared memory page
  uint32 h_mem;                   // Used to hold handle to shared memory page
  sem_t s_procs_completed;        // Semaphore used to wait until all spawned processes have completed
  char h_mem_str[10];             // Used as command-line argument to pass mem_handle to new processes
  char s_procs_completed_str[10]; // Used as command-line argument to pass page_mapped handle to new processes


  lock_t lock;
  char lock_str[10];

  sem_t full_sem;
  sem_t empty_sem;


  char full_sem_str[10];
  char empty_sem_str[10];



  if (argc != 2) {
    Printf("Usage: "); Printf(argv[0]); Printf(" <number of processes to create>\n");
    Exit();
  }

  // Convert string from ascii command line argument to integer number
  numprocs = dstrtol(argv[1], NULL, 10); // the "10" means base 10
  Printf("Creating %d processes\n", numprocs);

  // Allocate space for a shared memory page, which is exactly 64KB
  // Note that it doesn't matter how much memory we actually need: we 
  // always get 64KB
  if ((h_mem = shmget()) == 0) {
    Printf("ERROR: could not allocate shared memory page in "); Printf(argv[0]); Printf(", exiting...\n");
    Exit();
  }

  // Map shared memory page into this process's memory space
  if ((mc = (missile_code *)shmat(h_mem)) == NULL) {
    Printf("Could not map the shared page to virtual address in "); Printf(argv[0]); Printf(", exiting..\n");
    Exit();
  }
  
  Printf("h_mem = %p \n",h_mem);
  Printf("mc = %p \n",mc);
  // Put some values in the shared memory, to be read by other processes
  mc->numprocs = numprocs;
  mc->really_important_char = 'A';


  Printf("&mc->numprocs = %p\n",&(mc->numprocs));
  Printf("&mc->really_important_char = %p\n",&(mc->really_important_char));

  init_cb(&(mc->cb));
  
  Printf("&mc->cb = %p\n",&(mc->cb));
  Printf("mc->cb.head = %d\n",mc->cb.head);
  Printf("mc->cb.tail = %d\n",mc->cb.tail);
  Printf("mc->cb.buffer = %d\n",mc->cb.buffer[0]);

  // Circular_Buffer* cb;



  // Printf("cb = %p" ,cb);


  // init_cb(mc->cb);




  // Create semaphore to not exit this process until all other processes 
  // have signalled that they are complete.  To do this, we will initialize
  // the semaphore to (-1) * (number of signals), where "number of signals"
  // should be equal to the number of processes we're spawning - 1.  Once 
  // each of the processes has signaled, the semaphore should be back to
  // zero and the final sem_wait below will return.
  if ((s_procs_completed = sem_create(-(2*numprocs-1))) == SYNC_FAIL) {
    Printf("Bad sem_create in "); Printf(argv[0]); Printf("\n");
    Exit();
  }

  if ((full_sem = sem_create(0)) == SYNC_FAIL) {
    Printf("Bad sem_create in "); Printf(argv[0]); Printf("\n");
    Exit();
  }

  if ((empty_sem = sem_create(C_BUFFER_SIZE)) == SYNC_FAIL) {
    Printf("Bad sem_create in "); Printf(argv[0]); Printf("\n");
    Exit();
  }


  if ((lock = lock_create()) == SYNC_FAIL) {
    Printf("Lock Not Implemented "); Printf(argv[0]); Printf("\n");
    Exit();
  }


  // Setup the command-line arguments for the new process.  We're going to
  // pass the handles to the shared memory page and the semaphore as strings
  // on the command line, so we must first convert them from ints to strings.
  ditoa(h_mem, h_mem_str);
  ditoa(s_procs_completed, s_procs_completed_str);
  ditoa(lock, lock_str);

  ditoa(full_sem, full_sem_str);
  ditoa(empty_sem, empty_sem_str);

  // Now we can create the processes.  Note that you MUST end your call to
  // process_create with a NULL argument so that the operating system
  // knows how many arguments you are sending.
  for(i=0; i<1; i++) {
    process_create(PRODUCER_TO_RUN, h_mem_str, s_procs_completed_str,lock_str,full_sem_str,empty_sem_str, NULL);
    Printf("PRODUCER Process %d created\n", i);
  }

  for(i=0; i<numprocs; i++) {
    process_create(CONSUMER_TO_RUN, h_mem_str, s_procs_completed_str,lock_str,full_sem_str,empty_sem_str, NULL);
    Printf("CONSUMER Process %d created\n", i);
  }
  
    for(i=1; i<numprocs; i++) {
    process_create(PRODUCER_TO_RUN, h_mem_str, s_procs_completed_str,lock_str,full_sem_str,empty_sem_str, NULL);
    Printf("PRODUCER Process %d created\n", i);
  }

  // And finally, wait until all spawned processes have finished.
  if (sem_wait(s_procs_completed) != SYNC_SUCCESS) {
    Printf("Bad semaphore s_procs_completed (%d) in ", s_procs_completed); Printf(argv[0]); Printf("\n");
    Exit();
  }
  Printf("All other processes completed, exiting main process.\n");
}
