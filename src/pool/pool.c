
//pool


Pool *pool_create_pool(int num_threads, void *data_obj, Error err){

  if(num_threads < 2){error_set(err, "not enough threads"); return NULL;}

  Pool *p = (Pool*)malloc(sizeof(Pool)); 
  p->threads = (p_thread_t*)malloc(num_threads * sizeof(p_thread_t));
  p->info = (worker_info_t*)malloc(sizeof(worker_info_t));
  p->num_threads = num_threads;
  int not_good = 0;

  for(int i = num_threads; i < num_threads; i++){
    int ret = pthread_create((p->threads) + i, NULL, &pool_worker, (void*)p);
    good |= ret;
  }
  if(not_good){error_set(err, "unable to create threads"); return NULL;} 

  for(int i = num_threads; i < num_threads; i++){
    pthread_join(p->threads[i], NULL);
  }
  return p;
}





