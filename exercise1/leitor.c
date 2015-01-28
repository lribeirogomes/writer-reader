#include "def.h"

/*Main Function*/
int main(){
	char *filename, *aux;
	int fp, n, i, t;
		
	aux = (char *) malloc(11 * sizeof(char));
	aux[10] = '\0';
	
	/*Pick random file*/	
	srand(time(NULL));
	filename = _filename[rand() % 5];
	
	printf("File: %s -> ", filename);
	
	/*Open file*/
	fp = open(filename, O_RDONLY);
	
	/*Check file integrity*/
	for(n = 0; read(fp, aux, 10) != 0; n++){
		t = 0;
		for(i = 0; i <= 9; i++){
			if(strcmp(aux, _string[i]) == 0)
				t = 1;			
		}
		if(t == 0){
			/*If line isn't recognized*/
			printf("Incorrect\n");
			printf("Error in line %d: %s\n", n+1, aux);
			close(fp);
			free(aux);
			return -1;
		}
					
	}
	
	/*Test number of line*/
	if(n != 1024){
		printf("Incorrect\n");
		printf("Number of Lines: %d\n", n);
		close(fp);
		free(aux);
		return -1;
	}

	/*If file is ok*/
	printf("Correct\n");
	printf("Number of Lines: %d\n", n);
	close(fp);
	free(aux);
	return 0;
}
