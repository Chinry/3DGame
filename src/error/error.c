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

void error_free(in)




int error_check(Error *err){ 
  if(err->is_set){
    err->is_set = 0;
    (*(err->handler))(err);
  return 1;
  }
  return 0;
}
void error_set(Error, char *text);
void error_handle_console(Error err);
