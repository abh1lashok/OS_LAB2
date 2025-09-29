#include "lab2-api.h"
#include "usertraps.h"
#include "misc.h"

#include "spawn.h"

void main (int argc, char *argv[])
{
  missile_code *mc;        // Used to access missile codes in shared memory page
  uint32 N_N3;            // Handle to the shared memory page
  sem_t s_procs_completed; // Semaphore to signal the original process that we're done
int i;
int j;

  sem_t N3;
  sem_t N;
  if (argc != 5) { 
    Printf("Usage: "); Printf(argv[0]); Printf(" <handle_to_shared_memory_page> <handle_to_page_mapped_semaphore> <handle to lock>\n"); 
    Exit();
  } 

  // Convert the command-line strings into integers for use as handles
  N_N3 = dstrtol(argv[1], NULL, 10); // The "10" means base 10
  s_procs_completed = dstrtol(argv[4], NULL, 10);
  N3 = dstrtol(argv[2], NULL, 10);
  N = dstrtol(argv[3], NULL, 10);
  i = 0;
  
  while(i < N_N3){
    sem_wait(N3);
    Printf("3 N molecules are created\n");
    i++;
    for(j = 0; j < 2; j++){
    if(sem_signal(N)) Printf("Sem_N signal passed\n");
    }
  }
 

    
  
  if(sem_signal(s_procs_completed) != SYNC_SUCCESS) {
    Printf("Bad semaphore s_procs_completed (%d) in ", s_procs_completed); Printf(argv[0]); Printf(", exiting...\n");
    Exit();
  }
}
