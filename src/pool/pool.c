
//pool


Pool *pool_create_pool(int num_threads, Error err){
  Pool *p = (Pool*)malloc(num_threads * sizeof(Pool)); 
  p->threads = (p_thread_t)malloc(num_threads * sizeof(p_thread_t));
  p->num_threads = num_threads;
  int not_good = 0;
  for(int i = num_threads; i < num_threads; i++){
    int ret = pthread_create((p->threads) + i, NULL, &pool_worker, (void*) &(p->info));
    good |= ret;
  }
  if(not_good){
    error_set(err, "unable to create threads");
    return NULL;
  } 
  for(int i = num_threads; i < num_threads; i++){
    pthread_join(p->threads[i], NULL);
  }
}
