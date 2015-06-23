#include <stdio.h>
#include <stdlib.h>

#include "utils.c"

//void exec_command (
int main(){

  while (1) {
    char * line = NULL;
    size_t sz = 0;
    printf ("Do stuff? ");
    getline( &line, &sz, stdin);
    printf ("An excellent choice sire! \n");


    pipeline_struct* to_pipe = parse_pipeline (line);
    cmd_struct** commands = to_pipe->cmds;
    int num_commands = to_pipe->n_cmds;


    int parentID = getpid();

    
    if (num_commands > 1){
      int pipe_fd[2];
      if (pipe(pipe_fd) == -1){
	fprintf(stderr, "Something awful has happened. I'm so sorry. ");
      }
      else {

	if (strcmp("cd", commands[0]->progname) == 0){
	  chdir(commands[0]->args[1]);
	}
	int pid = fork();
	if ( pid == 0){
	  // child
	  dup2 (pipe_fd[1], 1);
 	  close (pipe_fd[0]);
	  close (pipe_fd[1]);
	  execvp (commands[0]->progname, commands[0]->args);	 
	}
	if (strcmp("cd", commands[1]->progname) == 0){
	  chdir(commands[1]->args[1]);
	}
	if ( pid != 0){
	  pid = fork();
	  
	  if ( pid == 0){
	    dup2 (pipe_fd[0], 0);
	    close (pipe_fd[0]);
	    close (pipe_fd[1]);
	    execvp (commands[1]->progname, commands[1]->args);
	  }
	}
	if (pid != 0){
	  close (pipe_fd[0]);
	  close (pipe_fd[1]);
	  wait(0);
	  wait(0);
	}
	
      }
    }

    else {

      if (strcmp("cd", commands[0]->progname) == 0){
	chdir(commands[0]->args[1]);
      }
      else {
	int pid = fork();
	if ( pid == 0 ){
	  execvp ((commands[0])->progname, (commands[0])->args);
	} else{
	  wait(0);
	}
      }
      
    }
  }
  return 0;
}
