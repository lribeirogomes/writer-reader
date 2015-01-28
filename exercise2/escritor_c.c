#include "def.h"

int main(){
	char *filename, *string;
	int fp, i, n;

	srand(time(NULL));

	for(i = 1; i <= 512; i++){
		
		/*Open random file*/	
		filename = _filename[rand() % 5];
		fp = open(filename, O_WRONLY | O_CREAT, S_IRWXU);

		/*Write random string*/
		string = _string[rand() % 10];
		for(n = 1; n <= 1024; n++)
			write(fp, string, 10);

		/*Close file*/
		close(fp);
	}
	
	return 0;
}
