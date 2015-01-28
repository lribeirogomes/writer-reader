#include "def.h"

int main(){
	struct timeval time_i, time_f;
	unsigned int dif;
	int x, n_pid;

	srand(time(NULL));

	gettimeofday(&time_i, NULL);
	
	for(x = 1; x <= 10; x++){
		n_pid = fork();
		if(n_pid == 0)
			execl("escritor_c", "escritor_c", NULL);
	}
	
	for(x = 1; x <= 10; x++)
		wait(NULL);
	
	gettimeofday(&time_f, NULL);

	dif = (time_f.tv_sec - time_i.tv_sec) *1000000 + (time_f.tv_usec - time_i.tv_usec);	
	
	printf("Done. (%f secs)\n", (float) dif/1000000);
	
	return 0;
}
