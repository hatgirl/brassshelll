#include <stdio.h>
#include <stdlib.h>

#include "utils.c"

int main(){

  while (1) {
    char * line = NULL;
    size_t sz = 0;
    printf ("Do stuff? ");
    getline( &line, &sz, stdin);
    printf ("An excellent choice sire! \n");

    cmd_struct* to_invoke = parse_command (line);
    char* prog = to_invoke->progname;
    char** args = to_invoke->args;
    int* redirect = to_invoke->redirect;

    int ind;
    int length = sizeof (args) / sizeof(args[0]);
    for (ind = 0; ind < length; ind++){
      if (strcmp ("|", args[ind]) == 0){
	//do special things
      }
    }

    if (strcmp("cd", prog) == 0){
      chdir(args[1]);
    }
    else {
      int pid = fork();
      if ( pid == 0 ){
	execvp (prog, args);
      } else{
        wait(0);
      }
    }
    
  }

  return 0;
}
