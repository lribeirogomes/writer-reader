#include "def.h"

/*Main Function*/
int main(){
	char *filename, *aux;
	int fp, n, i, t;
	
	aux = (char *) malloc(11 * sizeof(char));
	
	/*Pick random file*/	
	srand(time(NULL));
	filename = _filename[rand() % 5];
	
	/*Open file*/
	fp = open(filename, O_RDONLY);
	if(fp == -1){
		printf("%s not found!\n", filename);
		exit(-1);
	}
	
	/*Request shared lock*/ 
	if(flock(fp, LOCK_SH) == -1){
		printf("error %d\n", errno);
		close(fp);
		return -1;
	}
	
	printf("File: %s -> ", filename);
	
	/*Read first line*/
	if(read(fp, aux, 10) != 0){
		t = 0;
		for(i = 0; i <= 9; i++){
			if(strcmp(aux, _string[i]) == 0){
				t = 1;
				break;
			}
		}
		
		if(t == 0){
			/*If line isn't recognized*/
			printf("Incorrect\n");
			printf("Error in line 1: %s\n", aux);
			free(aux);
			close(fp);
			return -1;
		}
	}	
	/*If first line is empty*/
	else{
		printf("Incorrect\n");
		printf("File is empty!\n");
		free(aux);
		close(fp);
		return -1;
	}
	
	/*Check the rest of the file*/
	for(n = 1; read(fp, aux, 10) != 0; n++){
		if(strcmp(aux, _string[i]) != 0){
			/*If line isn't recognized*/
			printf("Incorrect\n");
			printf("Line %d is different: %s\n", n+1, aux);
			free(aux);
			close(fp);
			return -1;
		}
	}

	/*Free lock*/ 
	if(flock(fp, LOCK_UN) == -1){
		printf("error %d\n", errno);
		close(fp);
		return -1;
	}
	
	/*Test number of line*/
	if(n != 1024){
		printf("Incorrect\n");
		printf("Number of Lines: %d\n", n);
		free(aux);
		close(fp);
		return -1;
	}

	/*If file is ok*/
	printf("Correct\n");
	printf("Number of Lines: %d\n", n);
	free(aux);
	close(fp);
	return 0;
}
