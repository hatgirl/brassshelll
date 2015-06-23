#include <stdio.h>
#include <stdlib.h>

#include "utils.c"

int main(){

  while (1) {
    char * line = NULL;
    size_t sz = 0;
    getline( &line, &sz, stdin);
    
    cmd_struct* to_invoke = parse_command (line);
    char* prog = to_invoke->progname;
    char** args = to_invoke->args;
    int* redirect = to_invoke->redirect;
    execvp (prog, args);
  }


  return 0;
}
