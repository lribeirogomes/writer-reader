#include "def.h"

int main(){
	struct timeval time_i, time_f;
	unsigned int dif;
	int n;

	srand(time(NULL));

	gettimeofday(&time_i, NULL);
	
	/*Launch child processes*/
	for(n = 0; n < 10; n++){
		if(fork() == 0)
			execl("escritor_c", "escritor_c", NULL);
	}
	
	/*Wait for child processes*/
	for(n = 0; n < 10; n++)
		wait(NULL);
	
	/*Print execution time */
	gettimeofday(&time_f, NULL);

	dif = (time_f.tv_sec - time_i.tv_sec) *1000000 + (time_f.tv_usec - time_i.tv_usec);	
	
	printf("Done. (%f secs)\n", (float) dif/1000000);
	
	return 0;
}
