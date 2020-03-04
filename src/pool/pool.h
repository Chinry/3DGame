//pool
#include "../error/error.h"
#include "../data_struct/queue.h"

//worker_info_t
typedef struct{
     
}worker_info_t;


//Pool
typedef struct{
  pthread_t *queue_thread;
  pthread_t *threads; 
  int num_threads; 
  worker_info_t *info;
  void *data_obj;
  queue *q;
}Pool;






Pool *pool_create(int num_threads, Error err);
void *pool_worker(void *ptr);
void pool_queue(Pool *p, void *info, int (*job)(*void), int priority, Error err);
void pool_finish_all_jobs(Pool *p);
Pool *pool_destroy(Pool *p);
