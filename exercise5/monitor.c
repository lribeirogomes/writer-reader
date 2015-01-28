#include "def.h"

int main(int argc, char *argv[]){
	int size, pipefd[2];
	char buffer[B_SIZE] = "";
	pid_t w_pid, r_pid;
	
	printf("[Monitor] Started.\n");
	
	/*Initialize pipe here*/
	if (pipe(pipefd) == -1) {
        printf("[Monitor] Failed to create pipe. (%s)\n", strerror(errno));
        exit(-3);
    }

	/*Create process for writer*/
	if((w_pid = fork()) == 0){
		
		if(execl("escritor", "escritor", NULL) == -1) {
			printf("[Monitor] Failed to launch Writer. (%s)\n", strerror(errno));
			exit(-2);
		}
	}
	else if(w_pid == -1){
		printf("[Monitor] Failed to create fork for Writer process. (%s)\n", strerror(errno));
		exit(-1);
	}
	
	/*Create process for reader*/ /*if something fails kill writer?*/
	if((r_pid = fork()) == 0) {

		if(dup2(pipefd[0], STDIN_FILENO) == -1) {
			printf("[Monitor] Failed to setup pipe. (%s)\n", strerror(errno));
			exit(-3);
		}
		
		close(pipefd[1]);
		
		if(execl("leitor", "leitor", NULL) == -1) {
			printf("[Monitor] Failed to launch Reader. (%s)\n", strerror(errno));
			exit(-2);
		}

	} else if(r_pid == -1) {
		printf("[Monitor] Failed to create fork for Reader process. (%s)\n", strerror(errno));
		exit(-1);
	}
	
	close(pipefd[0]);	
	
	/*Main loop*/
	while(1){
	
		size = read(STDIN_FILENO, buffer, B_SIZE);
		buffer[size-1] = '\0';
		
		if(strcmp(buffer, "sair") == 0)
			break;
		
		else if(strcmp(buffer, "il") == 0) {
			if(kill(w_pid, SIGUSR1) == -1)
				printf("[Monitor] Failed to send signal SIGUSR1. (%s)\n", strerror(errno));
		}
				
		else if(strcmp(buffer, "ie") == 0) {
			if(kill(w_pid, SIGUSR2) == -1)
				printf("[Monitor] Failed to send signal SIGUSR2. (%s)\n", strerror(errno));
		}
			
		else if(write(pipefd[1], buffer, size) == -1) /* pipe may close on the other side */
			break;
	}
	
	if(kill(w_pid, SIGTSTP) == -1)
		printf("[Monitor] Failed to send signal SIGTSTP to Writer. (%s)\n", strerror(errno));
	else {
		if(waitpid(w_pid, NULL, 0) == -1)
			printf("[Monitor] Wait for Writer failed. (%s)\n", strerror(errno));
	}
		
 	if(write(pipefd[1], "sair\n", strlen("sair\n")) == -1)
 		printf("[Monitor] Failed to send terminate message to Reader. (%s)\n", strerror(errno));
 	else {
		if(waitpid(r_pid, NULL, 0) == -1)
			 printf("[Monitor] Wait for Reader failed. (%s)\n", strerror(errno));
	}
		
	close(pipefd[1]);	
	
	printf("[Monitor] Done.\n");
	
	return 0;
}

	
