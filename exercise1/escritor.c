#include "def.h"

/*Main Function*/
int main(){
	char *filename, *string;
	int fp, i, n;

	srand(time(NULL));

	for(i = 1; i <= 5120; i++){
		printf("%d\n", i);
		
		/*Pick random file*/	
		filename = _filename[rand() % 5];

		fp = open(filename, O_WRONLY | O_CREAT, S_IRWXU);

		/*Pick random string*/
		string = _string[rand() % 10];

		for(n = 1; n <= 1024; n++)
			write(fp, string, 10);

		close(fp);
	}
	printf("Done.\n");
	
	return 0;
}
