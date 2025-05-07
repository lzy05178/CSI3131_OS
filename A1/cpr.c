/* ------------------------------------------------ ------------
File: cpr.c

Last name: LIN
Student number: 300126813

Description: This program contains the code for creation
 of a child process and attach a pipe to it.
	 The child will send messages through the pipe
	 which will then be sent to standard output.

Explanation of the zombie process
(point 5 of "To be completed" in the assignment):

If a child process terminates before its parent process, but the parent process 
does not reclaim the child process to release resources occupied by the child process, 
the child process becomes a zombie process.

	(please complete this part);

------------------------------------------------------------- */
#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>
#include <stdlib.h>
static int BUF = 100;

/* Prototype */
void createChildAndRead (int);

/* -------------------------------------------------------------
Function: main
Arguments: 
	int ac	- number of command arguments
	char **av - array of pointers to command arguments
Description:
	Extract the number of processes to be created from the
	Command line. If an error occurs, the process ends.
	Call createChildAndRead to create a child, and read
	the child's data.
-------------------------------------------------- ----------- */

int main (int ac, char **av)
{
 int processNumber; 

 if (ac == 2)
 {
 if (sscanf (av [1], "%d", &processNumber)== 1)
 {
    createChildAndRead(processNumber);
 }
    else fprintf(stderr, "Cannot translate argument\n");
 }
    else fprintf(stderr, "Invalid arguments\n");
    return (0);
}


/* ------------------------------------------------ -------------
Function: createChildAndRead
Arguments: 
	int prcNum - the process number
Description:
	Create the child, passing prcNum-1 to it. Use prcNum
	as the identifier of this process. Also, read the
	messages from the reading end of the pipe and sends it to 
	the standard output (df 1). Finish when no data can
	be read from the pipe.
-------------------------------------------------- ----------- */

void createChildAndRead(int prcNum){
	if(prcNum == 1){ //base case 
		printf("Process 1 begins\n");
		sleep(5);
		printf("Process 1 ends\n");
	}else{
		printf("Process %d begins\n", prcNum);
		int fd[2];
		pipe(fd);

		int pid = fork();
		

		if(pid == 0){
			dup2(fd[1],8);
			char trans[BUF]; 
			sprintf(trans,"%d",prcNum-1);
			char *var[] = {"./cpr",trans,NULL};
			execvp(var[0],var);
			
			
		}
		close(fd[1]);
		char buf[BUF];
		int size;
		while ((size = read(fd[0],buf,BUF))>0){
			buf[size] = 0;//换行
			printf("%s",buf);
		}
		sleep(10);
		printf("Process %d ends\n",prcNum);
	}

 /* Please complete this function according to the
Assignment instructions. */
}



