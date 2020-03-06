#include <stdlib.h>
#include "queue.h"
queue *queue_init(int initial_nodes){ //not going to check for super small queues
  queue *q = (queue*)malloc(sizeof(queue));
  q->num_alloc_nodes = initial_nodes;
  q->initial_num_nodes = initial_nodes;
  q->nodes = (void**)malloc(sizeof(void*) * initial_nodes);
  q->top = q->bot = -1;
  q->total = 0;
}

void queue_free(queue *q){
  free(q->nodes);
  free(q);
}



void queue_add(queue *q, void *data){
  if (q->top == -1){
    q->total = 1; 
    q->top = q->bot = 0;
    (q->nodes)[0] = data;
  }
  else{
    if(q->total == (q->num_alloc_nodes - 4)) queue_realloc(q, 1);
    q->top = (q->top == (q->num_alloc_nodes - 1)) ? 0 : (q->top + 1); 
    (q->nodes)[q->top] = data;
    q->total++;
  }
}
void *queue_get(queue *q){
  if(q->bot == -1) return NULL;
  if(q->total == 1){
    int old_bot = q->bot;
    q->bot = q->top = -1;
    q->total = 0;
    return (q->nodes)[old_bot];
  } 
  int old_bot = q->bot;
  q->bot = (q->bot == (q->num_alloc_nodes - 1)) ? 0 : (q->bot + 1); 
  if((q->num_alloc_nodes > q->initial_num_nodes) && (q->total < (q->num_alloc_nodes / 16)) ){
    queue_realloc(q, 0);
    old_bot = 0;
  }
  q->total--;
  return (q->nodes)[old_bot];
}
void queue_realloc(queue *q, char enlarge){
  void **old_nodes = q->nodes;
  if(enlarge){
    q->nodes = (void**)malloc(sizeof(void*) * q->num_alloc_nodes * 2);
    int offset = q->bot;
    for(int i = 0; i < q->total; i++){
      if((i + offset) == q->num_alloc_nodes) offset = 0;
      (q->nodes)[i] = old_nodes[i + offset];
    }
    q->num_alloc_nodes = q->num_alloc_nodes * 2;
  }
  else{
    q->nodes = (void**)malloc(sizeof(void*) * (q->num_alloc_nodes / 2));
    int offset = q->bot;
    for(int i = 0; i < q->total; i++){
      if((i + offset) == q->num_alloc_nodes) offset = 0;
      (q->nodes)[i] = old_nodes[i + offset];
    }
    q->num_alloc_nodes = q->num_alloc_nodes / 2;
  }
  q->bot = 0;
  q->top = q->total - 1;
  free(old_nodes);
}
int queue_size(queue *q){
  return q->total;
}
