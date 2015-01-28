#include "def.h"

int main(){
	char *filename, *string;
	int fp, i, n;

	srand(time(NULL));

	for(i = 1; i <= 512; i++){
		
		/*Open random file*/	
		filename = _filename[rand() % 5];
		fp = open(filename, O_WRONLY | O_CREAT, S_IRWXU);
		
		/*Request exclusive lock*/
		if(flock(fp, LOCK_EX) == -1){
			printf("%d. error %d (lock)\n", i, errno);
			printf("process %d exited\n", getpid());
			close(fp);
			return -1;
		}
		
		/*Write random string*/
		string = _string[rand() % 10];
		for(n = 1; n <= 1024; n++)
			write(fp, string, 10);

		/*Free lock*/
		if(flock(fp, LOCK_UN) == -1){
			printf("%i. error %d (unlock)\n", i, errno);
			printf("process %d exited\n", getpid());
			close(fp);
			return -1;
		}
		
		/*Close file*/
		close(fp);

	}
	
	return 0;
}
