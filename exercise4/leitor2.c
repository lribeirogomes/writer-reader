#include "def.h"

pthread_t tid[3];
int status[3];

void endThread(int fp, int thread_num, int _status){
		if(flock(fp, LOCK_UN) == -1)
			printf("Error: %d\n", errno);
					
		close(fp);     
		status[thread_num] = _status;
		pthread_exit(NULL);
}


void *reader(void *arg){
	char *filename, aux[10];
	int fp, n, i, thread_num;

	aux[10] = '\0';

	filename = (char *) arg;
	
	/*Find out thread number*/
	for(i = 0; i < 3; i++){
		if(pthread_self() == tid[i]){
			thread_num = i;
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
	
	/*Read first line*/
	if(read(fp, aux, 10) != 0){
		/*compare it to stored strings*/
		n = 0;
		for(i = 0; i <= 9; i++){
			if(strcmp(aux, _string[i]) == 0){
				n = 1;
				break;
			}
		}
		
		if(n == 0){
			/*If line isn't recognized, return -1*/
			printf("%s -> Incorrect. Error in line 1: %s\n", filename, aux);
			endThread(fp, thread_num, -1);
			return NULL;
		}
	}	
	/*If first line is empty, return -1*/
	else{
		printf("%s -> Incorrect. File is empty!\n", filename);
		endThread(fp, thread_num, -1);
		return NULL;
	}
	
	/*Check the rest of the file*/
	for(n = 1; read(fp, aux, 10) != 0; n++){
		if(strcmp(aux, _string[i]) != 0){
			/*If line doesn't match, return -1*/
			printf("%s -> Incorrect. Line %d is different: %s\n", filename, n+1, aux);
			endThread(fp, thread_num, -1);
			return NULL;
		}
	}

	/*If the number of lines left is wrong, return -1*/
	if(n != 1024){
		printf("%s -> Incorrect. Number of Lines: %d\n", filename, n);
		endThread(fp, thread_num, -1);
		return NULL;
	}

	/*If file is ok, return 0*/
	printf("%s -> Correct\n", filename);
	endThread(fp, thread_num, -0);
	return NULL;
}



int main(){
	struct timeval time_i, time_f;
	unsigned int dif;
	int n;
	char files[3][13];
	
	/*Pick random files*/	
	srand(time(NULL));
	for(n = 0; n < 3; n++)
		sprintf(files[n], "SO2014-%d.txt", rand() % 5);

	gettimeofday(&time_i, NULL);
	
	/*Create threads*/
	for(n = 0; n < 3; n++){
		if(pthread_create(&(tid[n]), NULL, &reader, files[n]) != 0){
			printf("Can't create thread. Exiting...\n");
			return -1;
		}
	}
	
	/*Wait for threads to join*/
	for(n = 0; n < 3; n++){
		if(pthread_join(tid[n], NULL) != 0){
			printf("\nError. Exiting...\n");
			return -1;
		}
	}
	
	/*Print execution time */
	gettimeofday(&time_f, NULL);
	dif = (time_f.tv_sec - time_i.tv_sec) * 1000000 + (time_f.tv_usec - time_i.tv_usec);	
	printf("Done. (%f secs)\n", (float) dif / 1000000);
	
	/*Print return values*/
	printf("\nReturn values:\n");
	for(n = 0; n < 3; n++)
		printf("%d\n", status[n]);
	printf("\n");
		
	return 0;	
}
