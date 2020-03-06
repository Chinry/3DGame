//pool

enum workerMutex{
  Queue_Lock = 0, //accessing queue
  Busy_Lock,
  Thread_ID_Count_Lock,
  workerMutex_length 
};

enum workerCond{
  Queue_Empty = 0, //accessing queue
  workerCond_length 
};

struct workerInfo{
  pthread_mutex_t locks[(int)workerMutex_length];
  pthread_cond_t conds[(int)workerCond_length];
}


//Pool
typedef struct{
  pthread_t *threads; 
  int num_threads; 
  int tid_count;
  bool *busy; //1 not busy, 0 busy
  bool kill_all;
  struct workerInfo *info;
  queue *q;
}Pool;


//Job
typedef struct{
void *info;
int (*callback)(void*);
}Job;




Pool *pool_create(int num_threads, Error err);
void *pool_worker(void *ptr);
void pool_queue(Pool *p, Job *j);
bool pool_finish_jobs(Pool *p);
Pool *pool_destroy(Pool *p);
