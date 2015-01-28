#include "def.h"

/*Main Function*/
int main(){
	char *filename, *aux;
	int fp1, fp2;
		
 	aux = (char *) malloc(11 * sizeof(char));
	aux[10] = '\0';
	
	/*Pick 2 random files*/	
	srand(time(NULL));
	
	filename = _filename[rand() % 5];
	fp1 = open(filename, O_RDONLY);
	if(fp1 == -1){
		printf("%s not found!\n", filename);
		exit(-1);
	}
	printf("%s -> ", filename);
	
	filename = _filename[rand() % 5];
	fp2 = open(filename, O_WRONLY);
	if(fp2 == -1){
		printf("%s not found!\n", filename);
		exit(-1);
	}
	printf("%s\n", filename);

	/*Copy file1 to file2*/
	while(read(fp1, aux, 10) != 0){
		write(fp2, aux, 10);			
	}

	printf("Done.\n");
	close(fp1);
	close(fp2);
	free(aux);
	return 0;
}
