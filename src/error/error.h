//serve as a global error object
typedef struct error{
  char *message; //actual error message
  int size; 
  char is_set; // is the error set
  void (*handler)(struct error *, void *); //associate a function for logging or printing 
}Error;

//initialize an error object and size of message buffer in bytes
Error *error_new(int message_size);

void error_free(Error *err);

//handles error with error function, returns 1 if error, 0 if none
int error_check(Error *err);

//set text to print later
void error_set(Error *err, char *text);

//print error to console, maybe more options like logging in the future
void error_handle_console(Error *err, void *ptr);

//quick print the values of a data object
//will run through a struct or buffer 


void error_get_stuff(Error err, void *thing, //object to run through
                                size_t size, //number of bytes object spans
                                size_t align, //datatype
                                char* format); //number base to display in
