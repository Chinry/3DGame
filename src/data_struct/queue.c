#include "queue.h"
queue *queue_init(int initial_nodes){ //not going to check for super small queues
  queue *q = (queue*)malloc(sizeof(queue));
  q->num_nodes = initial_nodes;
  q->initial_num_nodes = initial_nodes;
  void **nodes = (void**)malloc(sizeof(void*) * intial_nodes);
  q->top = q->bot = -1;
  q->total = 0;
}
void queue_add(queue *q, void *data){
  if (q->top == -1){
    q->total = 1; 
    q->top = q->bot = 0;
    (q->nodes)[0] = data;
  }
  else{
    if(total == (num_alloc_nodes - 4)) queue_realloc(q, 1);
    q->top = (q->top == (q->num_alloc_nodes - 1)) ? 0 : (q->top + 1); 
    (q->nodes)[q->top] = data;
    q->total++;
  }
}
void *queue_get(queue *q){
  if(q->bot == -1) return NULL;
  if(q->total == 1){
    q->bot = q->top = -1;
    return (q->nodes)[q->bot];
    total = 0;
  } 
  q->bot = (q->bot == (q->num_alloc_nodes - 1)) ? 0 : (q->bot + 1); 
  if((num_alloc_nodes > initial_num_nodes) && (total < (num_alloc_nodes / 8)) )queue_realloc(q, 0);
  total--;
  return (q->nodes)[q->bot];
}
void queue_realloc(queue *q, bool enlarge){
  if(enlarge){
    void **old_nodes = q->nodes;
    q->nodes = (void**)malloc(sizeof(void*) * q->num_alloc_nodes * 2);
    int offset = q->bot;
    for(int i = 0; (i + offset) != q->top; i++){
      if((i + offset) > q-> num) offset = 0;
      (q->nodes)[i] = old_nodes[i + offset];
    }
    q->num_alloc_nodes = (q->num_alloc_nodes * 2);
    top = 0;
    bot = total - 1;
  }
  else{
    
  
  }
}
