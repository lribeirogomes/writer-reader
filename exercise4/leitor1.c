#include "def.h"

int main(){
	struct timeval time_i, time_f;
	unsigned int dif;
	int n, _status, status[3];
	char rand_n[3][2];
	
	/*Pick random numbers*/	
	srand(time(NULL));
	for(n = 0; n < 3; n++)
		sprintf(rand_n[n], "%d", rand() % 5);

	gettimeofday(&time_i, NULL);
	
	/*Launch child processes*/
	for(n = 0; n < 3; n++){
		if(fork() == 0)
			execl("leitor1_c", "leitor1_c", rand_n[n], NULL);
	}
	
	/*Wait for child processes*/
	for(n = 0; n < 3; n++){
		if(wait(&_status) == -1){
			printf("\nError. Exiting...\n");
			return -1;			
		}
		if(WIFEXITED(_status))
			status[n] = (char) WEXITSTATUS(_status);
		else{
			printf("Child process %d was interrupted.\n", n);
			return -1;
		}	
	}
	/*Print execution time */
	gettimeofday(&time_f, NULL);
	dif = (time_f.tv_sec - time_i.tv_sec) *1000000 + (time_f.tv_usec - time_i.tv_usec);	
	printf("Done. (%f secs)\n", (float) dif/1000000);
	
	/*Print return values*/
	printf("\nReturn values:\n");
	for(n = 0; n < 3; n++)
		printf("%d\n", status[n]);
	printf("\n");
	
	return 0;
}
