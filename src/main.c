#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "error/error.h"
#include "data_struct/queue.c"
#include "pool/pool.h"


int main(int argc, char **argv){
  Error *err = error_new(1024);
  err->handler = &error_handle_console;
  Pool *p = pool_create(4, err);
  if(engine_run){}
  return 0; 
}
