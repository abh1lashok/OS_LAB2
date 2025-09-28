#define C_BUFFER_SIZE 10

typedef struct Circular_Buffer{

int head;
int tail;

char buffer[C_BUFFER_SIZE] ;


} Circular_Buffer;

// static Circular_Buffer CB;

int put_item_cb(char c, Circular_Buffer* buf){
  
  buf->buffer[buf->head] = c;
  Printf("CB ---- Put %c in %d\n",c,buf->head);
  buf->head = (buf->head + 1)%C_BUFFER_SIZE;
  return 1;

}

int check_item_cb(char *c, Circular_Buffer* buf){
  

  *c = buf->buffer[buf->tail];
  Printf("CB ----  checking %c from %d\n",*c,buf->tail);
  // buf->tail = (buf->tail + 1)%C_BUFFER_SIZE;
  
  return 1;

}

int get_item_cb(char *c, Circular_Buffer* buf){
  

  *c = buf->buffer[buf->tail];
  Printf("CB ----  Got %c from %d\n",*c,buf->tail);
  buf->tail = (buf->tail + 1)%C_BUFFER_SIZE;
  
  return 1;

}

int is_full(Circular_Buffer* cb){

  if ((cb->head + 1)%C_BUFFER_SIZE == cb->tail) return 1;
  else return 0; 

}


int is_empty(Circular_Buffer* cb){
  if((cb->head == cb->tail)) return 1;
  else return 0; 
}


void init_cb(Circular_Buffer* cb){

  cb->head = 0;
  cb->tail = 0;

  
  Printf("Circular Buffer Initiated\n");


}

void Print_cb(Circular_Buffer* cb){
  int k;
  Printf(" Circular Buffer =>  ");

  for (k= 0;k < C_BUFFER_SIZE;k++){
    Printf("%c",cb->buffer[(k+cb->tail)%C_BUFFER_SIZE]);
  }
  Printf("\n");

}