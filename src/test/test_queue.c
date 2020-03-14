//test out queue functions
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


int main(int argc, char **argv){
  int get_data[200];
  int data[200];
  for(int i = 0; i < 200; i++)
    data[i] = i + 1;
  queue *q = queue_init(20);
  for(int j = 0; j < 5; j++){
    for(int i = 0; i < 200; i++)
      queue_add(q, (void*)(data + i));
    for(int i = 0; i < 200; i++){
      int ret = *((int*)queue_get(q));
      printf("%i ", ret);
    }
    printf("\n");
  } 
  queue_free(q);
  return 0;
}
