#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define MAX_PATH_LENGTH 256


typedef int (*ExtHandler)(const char *input_file, const char *output_buffer, int buffer_size, char *error_str, int error_len);

//ext_pair_t
typedef struct {
  char *extension;
  ExtHandler handler;
  int max_files;
  int offset;
}ext_pair_t;

//file_queue_t
typedef struct {
  char *name;
  char *path;
  ext_pair_t *ext;
}file_queue_t;


int obj_parse(const char *input_file, const char *output_buffer, int buffer_size, char *error_str, int error_len);
int csv_parse(const char *input_file, const char *output_buffer, int buffer_size, char *error_str, int error_len);

int create_wad(const char *header_file, const char *data_file, const char *dir_to_search, char **dirs, ext_pair_t *exts, char *error_str, int error_len);
int fill_file_queue(const char *path, char **dirs, ext_pair_t *exts, char *error_str, int error_len);
char error[1024];



char *acceptable_directories[] = {
  "assets",
  "maps",
  "models",
  0
};

ext_pair_t acceptable_extensions[] = {{"obj", &obj_parse, 31, NULL}, {"csv", &csv_parse, 31, NULL}, NULL};


void create_error(char *error, char *error_str, int error_len){
  snprintf(error_str, error_len * sizeof(char), "%s\n", error);
}

void setup_extensions(ext_pair_t *array, int *buffer_size, int *num_extensions){
  file_total = *buffer_size = 0;
  ext_total = *num_extensions = 0;
  for(int i = 0; ; i++){
    if(!(array[i])) break;
    array[i].offset = file_total;
    total += ((array[i]).max_files + 1);
  }
  ext_total = i;
}

int main(int argc, char **argv){
  if (create_wad("../../src/wad.h", "../../build/data.wad", "../../data", acceptable_directories, acceptable_extensions, error, 1024)){
    printf("%s", error);
  }
  return 0;
}

int create_wad(const char *header_file, const char *data_file, const char *dir_to_search, char **dirs, ext_pair_t *exts, char *error_str, int error_len){
  FILE *header_file_ptr = fopen(header_file, "w");
  FILE *data_file_ptr = fopen(data_file, "w");
  int buffer_size, num_extensions;
  setup_extensions(acceptable_extensions, &max_files, &num_extensions)
  file_queue_t master_queue[size;
  if (fill_file_queue(dir_to_search, dirs, exts, error_str, error_len)) return 1;
  fclose(header_file_ptr);
  fclose(data_file_ptr);
  return 0;
}


int fileOrDir(const char *path){
  //dir = -1, other = 0, file = 1
  struct stat stat_path;
  stat(path, &stat_path);
  if(S_ISDIR(stat_path.st_mode)){
    return -1;
  }
  if(S_ISREG(stat_path.st_mode)){
    return 1;
  }
  return 0;
}

int fill_file_queue(const char *path, char **dirs, ext_pair_t *exts, char *error_str, int error_len){
  char full_path[MAX_PATH_LENGTH];
  DIR *directory = opendir(path);
  if (directory){create_error("directory does not exist", error_str, error_len); return 0;}
  int filetype;
  struct dirent *entry;
  int i = 0;
  while((entry = readdir(directory))){
    memset(full_path, 0, MAX_PATH_LENGTH);
    strcpy(full_path, path); strcat(full_path, "/"); strcat(full_path, entry->d_name);
    filetype = fileOrDir(full_path);
    if(filetype == 1){


    }
    if(filetype == -1){



    }
  }
  closedir(path);
  return 1;
}
