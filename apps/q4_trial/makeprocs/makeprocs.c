#include "lab2-api.h"
#include "usertraps.h"
#include "misc.h"



#include "spawn.h"
// #include "CircularBuffer.h"
// #ifndef __CB__
// #define __CB__
// #include "CircularBuffer.h"
// #endif


#define NO_OF_PROCESSES 5
#define NO_OF_PRODUCERS 2
#define NO_OF_CONSUMERS 3
#define N_N3 2
#define N_H2O 6






void main (int argc, char *argv[])
{
  int numprocs = 0;               // Used to store number of processes to create
  int i;                          // Loop index variable
  missile_code *mc;               // Used to get address of shared memory page
  uint32 h_mem;                   // Used to hold handle to shared memory page
  sem_t s_procs_completed;        // Semaphore used to wait until all spawned processes have completed
  char h_mem_str[10];             // Used as command-line argument to pass mem_handle to new processes
  char s_procs_completed_str[10]; // Used as command-line argument to pass page_mapped handle to new processes
  int n_N3 ;
  int n_H2O;
  char n_N3_str[10];
  char n_H2O_str[10];


  // lock_t lock;
  // char lock_str[10];

  sem_t N3;
  sem_t H2O;
  sem_t N;
  sem_t O2;
  sem_t NO2;



  char N3_str[10];
  char H2O_str[10];
  char N_str[10];
  char O2_str[10];
  char NO2_str[10];


  // n_N3 = N_N3;
  // n_H2O = N_H2O;



  if (argc != 4) {
    Printf("Usage: "); Printf(argv[0]); Printf(" <number of processes to create>\n");
    Exit();
  }

  // Convert string from ascii command line argument to integer number
  numprocs = dstrtol(argv[1], NULL, 10); // the "10" means base 10
  Printf("Creating %d processes\n", numprocs);

  n_N3 =  dstrtol(argv[2], NULL, 10); // the "10" means base 10
  Printf("No of N3 %d \n", n_N3);

  n_H2O =  dstrtol(argv[3], NULL, 10); // the "10" means base 10
  Printf("No of H2O %d \n", n_H2O);


    ditoa(n_N3, n_N3_str);
  ditoa(n_H2O, n_H2O_str);


  // Allocate space for a shared memory page, which is exactly 64KB
  // Note that it doesn't matter how much memory we actually need: we 
  // always get 64KB
  // if ((h_mem = shmget()) == 0) {
  //   Printf("ERROR: could not allocate shared memory page in "); Printf(argv[0]); Printf(", exiting...\n");
  //   Exit();
  // }

  // // Map shared memory page into this process's memory space
  // if ((mc = (missile_code *)shmat(h_mem)) == NULL) {
  //   Printf("Could not map the shared page to virtual address in "); Printf(argv[0]); Printf(", exiting..\n");
  //   Exit();
  // }
  
  // Printf("h_mem = %p \n",h_mem);
  // Printf("mc = %p \n",mc);
  // // Put some values in the shared memory, to be read by other processes
  // mc->numprocs = numprocs;
  // mc->really_important_char = 'A';


  // Printf("&mc->numprocs = %p\n",&(mc->numprocs));
  // Printf("&mc->really_important_char = %p\n",&(mc->really_important_char));

  // init_cb(&(mc->cb));
  
  // Printf("&mc->cb = %p\n",&(mc->cb));
  // Printf("mc->cb.head = %d\n",mc->cb.head);
  // Printf("mc->cb.tail = %d\n",mc->cb.tail);
  // Printf("mc->cb.buffer = %d\n",mc->cb.buffer[0]);

  // Circular_Buffer* cb;



  // Printf("cb = %p" ,cb);


  // init_cb(mc->cb);




  // Create semaphore to not exit this process until all other processes 
  // have signalled that they are complete.  To do this, we will initialize
  // the semaphore to (-1) * (number of signals), where "number of signals"
  // should be equal to the number of processes we're spawning - 1.  Once 
  // each of the processes has signaled, the semaphore should be back to
  // zero and the final sem_wait below will return.
  if ((s_procs_completed = sem_create(-(numprocs-1))) == SYNC_FAIL) {
    Printf("Bad sem_create in "); Printf(argv[0]); Printf("\n");
    Exit();
  }
  
  // if ((lock = lock_create()) == SYNC_FAIL) {
  //   Printf("Lock Not Implemented "); Printf(argv[0]); Printf("\n");
  //   Exit();
  // }
   
  if ((N3 = sem_create(0)) == SYNC_FAIL) {
    Printf("Sem failed"); Printf(argv[0]);
    exit();
  }
  if ((O2 = sem_create(0)) == SYNC_FAIL){
    Printf("Sem failed"); Printf(argv[0]);
    exit();
  }
   if ((N = sem_create(0)) == SYNC_FAIL){
    Printf("Sem failed"); Printf(argv[0]);
    exit();
  }
   if ((NO2 = sem_create(0)) == SYNC_FAIL){
    Printf("Sem failed"); Printf(argv[0]);
    exit();
  }
   if ((H2O = sem_create(0)) == SYNC_FAIL){
    Printf("Sem failed"); Printf(argv[0]);
    exit();
  }
  // Setup the command-line arguments for the new process.  We're going to
  // pass the handles to the shared memory page and the semaphore as strings
  // on the command line, so we must first convert them from ints to strings.
  ditoa(h_mem, h_mem_str);
  ditoa(s_procs_completed, s_procs_completed_str);

  ditoa(N, N_str);
  ditoa(N3, N3_str);
  ditoa(H2O, H2O_str);
  ditoa(NO2, NO2_str);
  ditoa(O2, O2_str);
 
//  Printf("Lauda O2 value\n");
  Printf("N3 - %d\n", N3);
  Printf("O2 - %d\n", O2);
  Printf("N - %d\n", N);
  Printf("NO2 - %d\n", NO2);
  Printf("H2O - %d\n", H2O);

  Printf(N3_str);
  Printf(O2_str);
  Printf(N_str);
  Printf(NO2_str);
  Printf(H2O_str);
  // Now we can create the processes.  Note that you MUST end your call to
  // process_create with a NULL argument so that the operating system
  // knows how many arguments you are sending.

    //

    // N3 consumer
    process_create(N3_CONSUMER_TO_RUN, n_N3_str,N3_str, N_str, s_procs_completed_str, NULL);
    Printf("CONSUMER Process %d created\n", 1);
    // H20 consumer
    process_create(H2O_CONSUMER_TO_RUN, n_H2O_str, H2O_str, O2_str,s_procs_completed_str, NULL);
    Printf("CONSUMER Process %d created\n", 2);


        process_create(N3_PRODUCER_TO_RUN, n_N3_str,N3_str, s_procs_completed_str, NULL);
    Printf("PRODUCER N3 Process %d created\n", 1);

    process_create(H2O_PRODUCER_TO_RUN, n_H2O_str,H2O_str,s_procs_completed_str, NULL);
    Printf("PRODUCER H2O Process %d created\n", 2);

    // N and O2 consumer
    process_create(N_O2_CONSUMER_TO_RUN, n_N3_str, n_H2O_str, N_str, O2_str, NO2_str, s_procs_completed_str, NULL);
    Printf("CONSUMER Process %d created\n", 3);


  // And finally, wait until all spawned processes have finished.
  if (sem_wait(s_procs_completed) != SYNC_SUCCESS) {
    Printf("Bad semaphore s_procs_completed (%d) in ", s_procs_completed); Printf(argv[0]); Printf("\n");
    Exit();
  }
  Printf("All other processes completed, exiting main process.\n");
}
