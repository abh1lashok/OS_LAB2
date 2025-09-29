#include "lab2-api.h"
#include "usertraps.h"
#include "misc.h"
#include "spawn.h"
void main (int argc, char *argv[])
{
  missile_code *mc;        // Used to access missile codes in shared memory page
  uint32 N_H2O;            // Handle to the shared memory page
  sem_t s_procs_completed; // Semaphore to signal the original process that we're done
int i;
int j;
int k;
  sem_t H2O;
  sem_t O2;
  if (argc != 5) { 
    Printf("Usage: "); Printf(argv[0]); Printf(" <handle_to_shared_memory_page> <handle_to_page_mapped_semaphore> <handle to lock>\n"); 
    Exit();
  } 

  // Convert the command-line strings into integers for use as handles
  N_H2O = dstrtol(argv[1], NULL, 10); // The "10" means base 10
  s_procs_completed = dstrtol(argv[4], NULL, 10);
  H2O = dstrtol(argv[2], NULL, 10);
  O2 = dstrtol(argv[3], NULL, 10);
  i = 0;
  while(i < (N_H2O/2)){
    for(k = 0; k<2; k++){ if(sem_wait(H2O)) Printf("Sem_wait H2O signal passed\n");}
    Printf("O2 molecule is created\n");
    
    if(sem_signal(O2) == SYNC_SUCCESS) Printf("Sem_O2 signal passed\n\n");
    i++;
  }
 

    
  
  if(sem_signal(s_procs_completed) != SYNC_SUCCESS) {
    Printf("Bad semaphore s_procs_completed (%d) in ", s_procs_completed); Printf(argv[0]); Printf(", exiting...\n");
    Exit();
  }
}