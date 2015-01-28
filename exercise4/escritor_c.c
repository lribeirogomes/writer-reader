#include "def.h"

int main(){
	char filename[12];
	int fp, i, n, t;

	srand(time(NULL));

	for(t = 1; t <= 512; t++){
		
		/*Open random file*/		
		sprintf(filename, "SO2014-%d.txt", rand() % 5);
		fp = open(filename, O_WRONLY | O_CREAT, S_IRWXU);
		
		/*Request exclusive lock*/
		if(flock(fp, LOCK_EX) == -1){
			printf("%d. error %d (lock)\n", t, errno);
			printf("process %d exited\n", getpid());
			close(fp);
			return -1;
		}
		
		/*Write random string*/
		i = rand() % 10;
		for(n = 1; n <= 1024; n++)
			write(fp, _string[i], 10);

		/*Free lock*/
		if(flock(fp, LOCK_UN) == -1){
			printf("%d. error %d (unlock)\n", t, errno);
			printf("process %d exited\n", getpid());
			close(fp);
			return -1;
		}
		
		/*Close file*/
		close(fp);

	}
	
	return 0;
}
