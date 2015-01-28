#include "def.h"

#define N_THREADS 10

pthread_t tid[N_THREADS];
int status[N_THREADS];
int i = -1;

void endThread(int fp, int thread_num, int _status){
		if(flock(fp, LOCK_UN) == -1)
			printf("Error: %d\n", errno);
					
		close(fp);     
		status[thread_num] = _status;
		pthread_exit(NULL);
}


void *sectionReader(void *arg){
	char *filename, aux[10];
	int fp, n, t, n_lines, thread_num;

	aux[10] = '\0';

	filename = (char *) arg;
	n_lines = 1024/N_THREADS;
	
	/*Find out thread number*/
	for(n = 0; n < N_THREADS; n++){
		if(pthread_self() == tid[n]){
			thread_num = n;
			break;
		}
	}
	
	/*Open file*/
	fp = open(filename, O_RDONLY);
	if(fp == -1){
		printf("File %s not found!\n", filename);
		status[thread_num] = -1;
		pthread_exit(NULL);
		return NULL;
	}
	
	/*Request shared lock*/ 
	if(flock(fp, LOCK_SH) == -1){
		printf("Error: %d\n", errno);
		close(fp);
		status[thread_num] = -1;
		pthread_exit(NULL);
		return NULL;
	}
	
	/*Adjust file pointer*/
	if(lseek(fp, n_lines*thread_num*10*sizeof(char) , SEEK_SET) == -1){
		printf("Error: %d\n", errno);
		endThread(fp, thread_num, -1);
		return NULL;
	}
	
	/*Read file*/
	for(n = 0; n < n_lines; n++){
		if(read(fp, aux, 10) == 0){
			endThread(fp, thread_num, -1);    /*If line is empty, return -1*/
			return NULL;
		}
				
		/*If it's the first line read*/
		if(i == -1){
			for(t = 0; t <= 9; t++){
				if(strcmp(aux, _string[t]) == 0)    /*compare it to stored strings*/
					i = t;
			}
			if(i == -1){
				endThread(fp, thread_num, -1);    /*If line isn't recognized, return -1*/
				return NULL;
			}				
		}
	
		if(strcmp(aux, _string[i]) != 0){
			endThread(fp, thread_num, -1);    /*If line doesn't match, return -1*/
			return NULL;	
		}
	}
	
	/*If it's the last thread*/
	if(thread_num == N_THREADS - 1){
		/*Read all the lines left*/    
		for(n = 0; read(fp, aux, 10) != 0; n++){	
			if(strcmp(aux, _string[i]) != 0){				
				endThread(fp, thread_num, -1);    /*If line doesn't match, return -1*/
				return NULL;
			}
		}
		
		if(n_lines*N_THREADS + n != 1024){
			endThread(fp, thread_num, -1);    /*If the number of lines is wrong, return -1*/
			return NULL;
		}
	}

	endThread(fp, thread_num, 0);    /*If file is ok, return 0*/
	return NULL;
}


int main(){
	struct timeval time_i, time_f;
	unsigned int dif;
	int n;
	char filename[13];

	
	/*Pick random file*/
	srand(time(NULL));
	sprintf(filename, "SO2014-%d.txt", rand() % 5);

	gettimeofday(&time_i, NULL);
	
	/*Create threads*/
	for(n = 0; n < N_THREADS; n++){
		if(pthread_create(&(tid[n]), NULL, &sectionReader, filename) != 0){
			printf("Can't create thread. Exiting...\n");
			return -1;
		}
	}
	
	/*Wait for threads to join*/
	for(n = 0; n < N_THREADS; n++){
		if(pthread_join(tid[n], NULL) != 0){
			printf("\nError. Exiting...\n");
			return -1;
		}
	}
	
	i = 0;
	for(n = 0; n < N_THREADS; n++){
		if(status[n] != 0)
			i = -1;
	}
	if(i == 0)
		printf("%s -> Correct\n", filename);
	else
		printf("%s -> Incorrect\n", filename);
	
	/*Print execution time */
	gettimeofday(&time_f, NULL);
	dif = (time_f.tv_sec - time_i.tv_sec) * 1000000 + (time_f.tv_usec - time_i.tv_usec);	
	printf("Done. (%f secs)\n", (float) dif / 1000000);
	
	/*Print return values*/	
	printf("\nReturn values:\n");
	for(n = 0; n < N_THREADS; n++)
		printf("%d\n", status[n]);
	printf("\n");
	
	return 0;	
}
