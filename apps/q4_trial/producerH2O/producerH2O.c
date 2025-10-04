#include "lab2-api.h"
#include "usertraps.h"
#include "misc.h"

#include "spawn.h"

void main (int argc, char *argv[])
{
  missile_code *mc;        // Used to access missile codes in shared memory page
  uint32 N_H2O;            // Handle to the shared memory page
  sem_t s_procs_completed; // Semaphore to signal the original process that we're done
  sem_t H2O;
  int i;
  // Printf("IN Producer H2O - %d \n",argc);
  if (argc != 4) { 
    Printf("Usage: "); Printf(argv[0]); Printf(" <handle_to_shared_memory_page> <handle_to_page_mapped_semaphore> <handle to lock>\n"); 
    Exit();
  } 

  // Convert the command-line strings into integers for use as handles
  N_H2O = dstrtol(argv[1], NULL, 10); // The "10" means base 10
  s_procs_completed = dstrtol(argv[3], NULL, 10);
  H2O = dstrtol(argv[2], NULL, 10);
  
  while(i< N_H2O){
  Printf("An H2O molecule is created \n");

  // if(sem_signal(H2O)) Printf("sem_H2O signal passed \n\n");
  sem_signal(H2O);
    i++;   
  }
  // Signal the semaphore to tell the original process that we're done
  // Printf("PROD - PID %d is complete.\n", Getpid());
  if(sem_signal(s_procs_completed) != SYNC_SUCCESS) {
    Printf("Bad semaphore s_procs_completed (%d) in ", s_procs_completed); Printf(argv[0]); Printf(", exiting...\n");
    Exit();
  }
}