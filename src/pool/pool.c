#include <stdlib.h>
#include <pthread.h>
#include "../error/error.h"
#include "../data_struct/queue.h"
#include "pool.h"
//pool


Pool *pool_create(int num_threads, Error *err){
  char not_good;
  Pool *p = (Pool*)malloc(sizeof(Pool)); 
  p->threads = (pthread_t*)malloc(num_threads * sizeof(pthread_t));
  p->info = (struct workerInfo*)malloc(sizeof(struct workerInfo));
  p->num_threads = num_threads;
  p->busy = (char*)malloc(sizeof(char) * num_threads); 
  p->q = queue_init(20);
  p->tid_count = 0;
  p->kill_all = 0;

  for(int i = 0; i < num_threads; i++)
    p->busy[i] = 1;


  //not_good = p && p->threads && p->info && p->num_threads && p->q;
  //if(not_good) goto cleanup;
  
  for(int i = 0; i < workerMutex_length; i++){
    pthread_mutex_init(&(p->info->locks[i]), NULL);
  }

  for(int i = 0; i < workerCond_length; i++){
    pthread_cond_init(&(p->info->conds[i]), NULL);
  }

  for(int i = 0; i < num_threads; i++){
    int ret = pthread_create((p->threads) + i, NULL, &pool_worker, (void*)p);
    //not_good = (!ret && not_good);
  }
  /*
  if(not_good){
  cleanup:
    error_set(err, "unable to create threads"); 
    return NULL;
  } 
  */
  return p;
}

void *pool_worker(void *ptr){
  int (*callback)(void*);
  int tid;
  int busy;
  Pool *p = (Pool*)ptr;
  Job *job;
  pthread_mutex_lock(&(p->info->locks[Thread_ID_Count_Lock]));
    tid = p->tid_count;
    (p->tid_count)++;
  pthread_mutex_unlock(&(p->info->locks[Thread_ID_Count_Lock]));
  for(;;){ 
    pthread_mutex_lock(&(p->info->locks[Queue_Lock]));
      while((job = (Job*)queue_get(p->q)) == NULL){
        pthread_mutex_lock(&(p->info->locks[Busy_Lock])); 
          (p->busy)[tid] = 0;
          busy = 0;
          for(int i = 0; i < p->num_threads; i++)
            busy = (busy || p->busy[i]);
          if(!busy)
            pthread_cond_signal(&(p->info->conds[None_Busy]));
        pthread_mutex_unlock(&(p->info->locks[Busy_Lock])); 
        pthread_cond_wait(&(p->info->conds[Queue_Empty]), &(p->info->locks[Queue_Lock]));
        if(p->kill_all) {
          pthread_mutex_unlock(&(p->info->locks[Queue_Lock])); 
          pthread_exit(NULL);}
      }
    pthread_mutex_unlock(&(p->info->locks[Queue_Lock])); 
    pthread_mutex_lock(&(p->info->locks[Busy_Lock])); 
      (p->busy)[tid] = 1;
    pthread_mutex_unlock(&(p->info->locks[Busy_Lock])); 
    callback = job->callback;
    (*callback)(job->info);
  }
}

void pool_queue(Pool *p, Job *j){
  void *data = (void *)j; 
  pthread_mutex_lock(&(p->info->locks[Queue_Lock]));
    queue_add(p->q, data);
    pthread_cond_signal(&(p->info->conds[Queue_Empty]));
  pthread_mutex_unlock(&(p->info->locks[Queue_Lock]));
}



void pool_finish_jobs(Pool *p){
  char busy = 0;
  pthread_mutex_lock(&(p->info->locks[Busy_Lock])); 
    while(busy){
      for(int i = 0; i < p->num_threads; i++)
        busy = (busy || p->busy[i]);
      pthread_cond_wait(&(p->info->conds[None_Busy]), &(p->info->locks[Busy_Lock]));
      busy = 0;
      for(int i = 0; i < p->num_threads; i++)
        busy = (busy || p->busy[i]);
    }
  pthread_mutex_unlock(&(p->info->locks[Busy_Lock])); 
}

void pool_destroy(Pool *p){
  pool_finish_jobs(p);
  p->kill_all = 1;
  pthread_cond_broadcast(&(p->info->conds[Queue_Empty]));
  for(int i = 0; i < p->num_threads; i++)
    pthread_join((p->threads)[i], NULL);    
  queue_free(p->q);      
  free(p->busy);
  for(int i = 0; i < workerMutex_length; i++){
    pthread_mutex_destroy(&(p->info->locks[i]));
  }
  for(int i = 0; i < workerCond_length; i++){
    pthread_cond_destroy(&(p->info->conds[i]));
  } 
  free(p->info);
  free(p->threads);
  free(p);
}

//at least one but spurious unblocks;
