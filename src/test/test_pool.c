#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "../error/error.h"
#include "../data_struct/queue.h"
#include "../pool/pool.h"


int numbers[128];
Job jobs[128];

int print_info(void *info){
  int num = *((int *)info);
  num++;
  fprintf(stdout, "%i\n", num);
  return 0;
}





int main(int argc, char **argv){
  for(int i = 0; i < 128; i++){
    numbers[i] = i; 
    jobs[i].info = (void*)(numbers + i);
    jobs[i].callback = &print_info;
  } 
  Error *err = error_new(1024);
  Pool *p = pool_create(4, err);
  for(int i = 0; i < 128; i++)
    pool_queue(p, &(jobs[i]));
  for(int j = 0; j < 1000000000; j++){}
  pool_destroy(p);
}
