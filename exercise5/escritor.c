
#include "def.h"

pthread_t tid[W_THREADS];
int lock = W_LOCK;
int errors = W_ERRORS;
int stop = 0;

void handler(int sig){
	/*handle SIGUSR1 signal*/
	if(sig == SIGUSR1){
		if(lock == 1){
			lock = 0;
			printf("[Writer] Locks Off.\n");
		} else {
			lock = 1;
			printf("[Writer] Locks On.\n");
		}
	}
	/*handle SIGUSR2 signal*/
	else if(sig == SIGUSR2){
		if(errors == 1){
			errors = 0;
			printf("[Writer] Errors Off.\n");
		} else {
			errors = 1;
			printf("[Writer] Errors On.\n");
		}
	}
	/*handle SIGTSTP signal*/
	else if(sig == SIGTSTP)
		stop = 1;
}


/*Set signal handlers*/
void setHandlers(){
	struct sigaction a;
	
	a.sa_handler = handler;
	sigemptyset(&a.sa_mask);
	
	sigaddset(&a.sa_mask, SIGUSR1);
	sigaddset(&a.sa_mask, SIGUSR2);
	sigaddset(&a.sa_mask, SIGTSTP);
	
	a.sa_flags = 0;
	
	sigaction(SIGUSR1, &a, NULL);
	sigaction(SIGUSR2, &a, NULL);
	sigaction(SIGTSTP, &a, NULL);
}



void *writer(){
	char filename[12], aux[10];
	int fp, i, n, _lock, _errors;

	while(!stop){
		/*Update switches*/
		_lock = lock;
		_errors = errors;
		
		/*Open random file*/		
		sprintf(filename, "SO2014-%d.txt", rand() % 5);
		fp = open(filename, O_WRONLY | O_CREAT, S_IRWXU);
		if(fp == -1){
			printf("[Writer] Failed to writer file %s.\n", filename);
			continue;
		}
		
		if(_lock){
			/*Request exclusive lock*/
			if(flock(fp, LOCK_EX) == -1){
				printf("[Writer] Failed to lock file %s (%s)\n", filename, strerror(errno));
				close(fp);
				continue;
			}
		}
		
		/*Write random string*/
		i = rand() % 10;
		for(n = 1; n <= 1024; n++){
			if(_errors){
				strcpy(aux, _string[i]);
				if(n % 2 == 0)
					aux[rand() % 9] = 'X';
				write(fp, aux, 10);	/*Write string with errors*/
			}
			else
				write(fp, _string[i], 10); /*Write string without errors*/
		}
		if(_lock){
			/*Free lock*/
			if(flock(fp, LOCK_UN) == -1){
				printf("[Writer] Failed to unlock file %s. (%s)\n", filename, strerror(errno));
				close(fp);
				return NULL;
			}
		}
		
		/*Close file*/
		close(fp);
	}
	
	return NULL;
}

int main(){
	int n;
	
	setHandlers();
	srand(time(NULL));
	
	printf("[Writer] Started.\n");
	
	/*Create threads*/
	for(n = 0; n < W_THREADS; n++){
		if(pthread_create(&(tid[n]), NULL, &writer, NULL) != 0){
			printf("[Writer] Failed to create thread.\n");
			return -1;
		}
	}

	printf("[Writer] Threads created.\n");
	
	/*Wait for threads to join*/
	for(n = 0; n < W_THREADS; n++){
		if(pthread_join(tid[n], NULL) != 0){
			printf("[Writer] Failed to join threads.\n");
			return -1;
		}
	}

	printf("[Writer] Threads terminated.\n");

	printf("[Writer] Done.\n");
	
	return 0;
}



