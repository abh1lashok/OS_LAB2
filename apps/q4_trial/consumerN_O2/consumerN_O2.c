#include "lab2-api.h"
#include "usertraps.h"
#include "misc.h"
#include "spawn.h"
int min (uint32 a, uint32 b){
    uint32 min;
    if( a > b){
        min = b;
    }
    else{
        min = a;
    }
    return min;
}
void main (int argc, char *argv[])
{
  missile_code *mc;        // Used to access missile codes in shared memory page
  uint32 N_H2O;            // Handle to the shared memory page
  uint32 N_N3;
  sem_t s_procs_completed; // Semaphore to signal the original process that we're done
int i;
int j;
int k;
  sem_t N;
  sem_t NO2;
  sem_t O2;
  if (argc != 7) { 
    Printf("Usage: "); Printf(argv[0]); Printf(" <handle_to_shared_memory_page> <handle_to_page_mapped_semaphore> <handle to lock>\n"); 
    Exit();
  } 

  // Convert the command-line strings into integers for use as handles
  N_N3 = dstrtol(argv[1], NULL, 10); // The "10" means base 10
  N_H2O = dstrtol(argv[2], NULL, 10); // The "10" means base 10
  s_procs_completed = dstrtol(argv[6], NULL, 10);
  N = dstrtol(argv[3], NULL, 10);
  O2 = dstrtol(argv[4], NULL, 10);
  NO2 = dstrtol(argv[5], NULL, 10);
  i = (3*N_N3);
  j = N_H2O/2;
  while(min(i, j)){
        if(sem_wait(O2)) Printf("Sem_wait of O2 passed \n");
        if(sem_wait(N)) Printf("Sem_wait of N is passed \n");
        Printf("An NO2 molecule is created \n");
        if(sem_signal(NO2)) Printf("Sem_signal of NO2 is passed \n");
  }
 

    
  
  if(sem_signal(s_procs_completed) != SYNC_SUCCESS) {
    Printf("Bad semaphore s_procs_completed (%d) in ", s_procs_completed); Printf(argv[0]); Printf(", exiting...\n");
    Exit();
  }
}