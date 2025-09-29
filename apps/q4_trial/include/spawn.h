#ifndef __USERPROG__
#define __USERPROG__

#ifndef __CB__
#define __CB__
#include "CircularBuffer.h"
#endif

typedef struct missile_code {
  int numprocs;
  char really_important_char;
  Circular_Buffer cb;

} missile_code;


#define N3_PRODUCER_TO_RUN "producerN3.dlx.obj"
#define H2O_PRODUCER_TO_RUN "producerH2O.dlx.obj"
#define H2O_CONSUMER_TO_RUN "consumerH2O.dlx.obj"
#define N_O2_CONSUMER_TO_RUN "consumerN_O2.dlx.obj"
#define N3_CONSUMER_TO_RUN "consumerN3.dlx.obj"

#endif