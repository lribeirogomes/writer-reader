#include "def.h"

pthread_t tid[R_THREADS];

pthread_mutex_t mutex;
sem_t sem;


char filebuffer[FB_SIZE][13];
int stop = 0;
int ri = 0;
int wi = 0;


void closeFile(int fp, char *filename){
	if(flock(fp, LOCK_UN) == -1)
		printf("[Reader] Failed to unlock file %s. (%s)\n", filename, strerror(errno));
	close(fp);	
}

void checkFile(char *filename){
	char aux[11];
	int fp, i, n;
	
	aux[10] = '\0';
	
	/*Open file*/
	fp = open(filename, O_RDONLY);
	if(fp == -1){
		printf("[Reader] File %s not found!\n", filename);
		return;
	}
	
	/*Request shared lock*/ 
	if(flock(fp, LOCK_SH) == -1){
		printf("[Reader] Failed to lock file %s. (%s)\n", filename, strerror(errno));
		close(fp);
		return;
	}
	
	/*Test if file is empty*/
	if(read(fp, aux, 10) == 0){	
		printf("[Reader] %s -> Incorrect. File is empty!\n", filename);
		closeFile(fp, filename);
		return;
	}

	/*Test if first line is correct*/
	for(i = 0; i <= 9; i++){
		if(strcmp(aux, _string[i]) == 0)
			break;
		else if(i == 9){
			printf("[Reader] %s -> Incorrect. Error in line 1: %s\n", filename, aux);
			closeFile(fp, filename);
			return;
		}			
	}

	/*Test if the rest of the lines match the first one*/
	for(n = 1; read(fp, aux, 10) != 0; n++){
		if(strcmp(aux, _string[i]) != 0){
			printf("[Reader] %s -> Incorrect. Line %d is different: %s\n", filename, n+1, aux);
			closeFile(fp, filename);
			return;
		}
	}

	/*Test if the number of lines is ok*/
	if(n != 1024){
		printf("[Reader] %s -> Incorrect. Number of Lines: %d\n", filename, n);
		closeFile(fp, filename);
		return;
	}
	
	printf("[Reader] %s -> Correct.\n", filename);
	closeFile(fp, filename);  
}


void *reader(){
	char filename[13];
	
	while(1){
		sem_wait(&sem);
		
		if(stop) break;

		pthread_mutex_lock(&mutex);
		
		strcpy(filename, filebuffer[ri]);
		ri = (ri + 1) % FB_SIZE;
		
		pthread_mutex_unlock(&mutex);
		
		checkFile(filename);
	}
	
	pthread_exit(NULL);
	return NULL;
}



int main(){
	char buffer[B_SIZE];
	int n, size;
	char *aux, *str;
	
	if(pthread_mutex_init(&mutex, NULL) == -1) {
		printf("[Reader] Failed to initialize mutex.\n");
		return -2;
	}
	
	if(sem_init(&sem, 0, 0) == -1) {
		printf("[Reader] Failed to initialize semaphore.\n");
		return -3;
	}
	
	
	printf("[Reader] Started.\n");
	
	/*Create threads*/
	for(n = 0; n < R_THREADS; n++){
		if(pthread_create(&(tid[n]), NULL, &reader, NULL) != 0){
			printf("[Reader] Failed to create thread.\n");
			return -1;
		}
	}
	
	printf("[Reader] Threads created.\n");
	
	while(!stop){
		
		if((size = read(STDIN_FILENO, buffer, B_SIZE)) > 0) {
		
			buffer[size-1] = '\0';
					
			if(strcmp(buffer, "sair") == 0){
				stop = 1;
				for(n = 0; n < R_THREADS; n++)
					sem_post(&sem);
			}
					
			str = buffer;
			
			while(!stop) {
				aux = strtok(str, " ");
				if(aux == NULL) break;
				
				str = NULL;				
				
				if(strlen(aux) > 12)
					aux[12] = '\0';
			
				strcpy(filebuffer[wi], aux);
				wi = (wi + 1) % FB_SIZE;
				sem_post(&sem);
			}
		}
	}

	/*Wait for threads to join*/
	for(n = 0; n < R_THREADS; n++){
		if(pthread_join(tid[n], NULL) != 0){
			printf("[Reader] Failed to join threads.\n");
			return -1;
		}
	}

	printf("[Reader] Threads terminated.\n");

	
	if(pthread_mutex_destroy(&mutex) == -1)
		printf("[Reader] Failed to destroy mutex.\n");
	
	if(sem_destroy(&sem) == -1)
		printf("[Reader] Failed to destroy semaphore.\n");


	printf("[Reader] Done.\n");

	return 0;
	
}







	

