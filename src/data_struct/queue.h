
//dynamically sized queue




//queue
typedef struct{
  int initial_num_nodes;
  int num_alloc_nodes; //number of allocated nodes
  int total; //number of nodes that have data
  int top;
  int bot; 
  void **nodes;
}queue;

void queue_realloc(queue *q, char enlarge);
void queue_add(queue *q, void *data);
queue *queue_init(int nodes);
void *queue_get(queue *q);
