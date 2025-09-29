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

#define PRODUCER_TO_RUN "producer.dlx.obj"
#define CONSUMER_TO_RUN "consumer.dlx.obj"

#endif