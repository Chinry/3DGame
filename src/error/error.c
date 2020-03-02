#include <stdio.h>
#include <stdlib.h>


Error *error_new(int message_size){
  Error *err = (Error*)calloc(sizeof(Error)); 
  char *message = (char*)malloc(message_size * sizeof(char));
  err->message = message;
  err->size = message_size;
  if (!(err && message)) return NULL;
  return err;
}

void error_free(Error *err){
  free(err->message);
  err-> = NULL;
  free(err);
}

int error_check(Error *err){
  if(err->is_set){
    (*(err->handler))(err);
    return 0; 
  }
  return 1;
}



void error_set(Error *err, char *text){
  err->is_set = 1; 
  snprintf(err->message, err->size, "error: %s\n", text);
}
void error_handle_console(Error err){
  printf("%s", err->message);
}

/*
void error_get_stuff(Error err, void *thing, size_t size, int align, char* format){
  unsigned char byte;
  for(int i = 0; i < size; i++){
    
  } 
}
*/
