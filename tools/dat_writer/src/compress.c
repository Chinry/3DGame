#include "../lib/lz4/lz4.h"
#include <libguile.h>

SCM compress_and_write(SCM source, SCM inputSize){
  char * malloc(   
  LZ4_compress_default(/* const char* */ source,
                    /* char* */ dest,
                    /* int */ inputSize,
                    /* int */  outputSize);

}


SCM allocate(SCM size){
  
}




void init_exports(){
  scm_c_define_gsubr("compress", 1, 
  scm_c_define_gsubr("allocate", 
}
