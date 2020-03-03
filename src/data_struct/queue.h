
//dynamically sized queue




//queue
typedef struct{
  int inital_num_nodes;
  int num_alloc_nodes; //number of allocated nodes
  int total; //number of nodes that have data
  int top;
  int bot; 
  void **nodes;
}queue;


void queue_add(Error err);
queue *queue_init(int nodes);
void *queue_get();
