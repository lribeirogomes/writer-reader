#include "def.h"

/*Main Function*/
int main(int argc, char *argv[]){
	char filename[12], aux[10];
	int fp, n, i;
	
	aux[10] = '\0';
	
	/*Test number of arguments*/
	if(argc != 2){
		printf("Invalid number of arguments.\n");
		return -1;
	}
	
	sprintf(filename, "SO2014-%s.txt", argv[1]);

	/*Open file*/
	fp = open(filename, O_RDONLY);
	if(fp == -1){
		printf("File %s not found!\n", filename);
		return -1;
	}
	
	/*Request shared lock*/ 
	if(flock(fp, LOCK_SH) == -1){
		printf("Error: %d\n", errno);
		close(fp);
		return -1;
	}
		
	/*Read first line*/
	if(read(fp, aux, 10) != 0){
		/*compare it to stored strings*/
		n = 0;
		for(i = 0; i <= 9; i++){
			if(strcmp(aux, _string[i]) == 0){
				n = 1;
				break;
			}
		}
		
		if(n == 0){
			/*If line isn't recognized, return -1*/
			printf("%s -> Incorrect. Error in line 1: %s\n", filename, aux);
			if(flock(fp, LOCK_UN) == -1)
				printf("Error: %d\n", errno);
			close(fp);
			return -1;
		}
	}	
	/*If first line is empty, return -1*/
	else{
		printf("%s -> Incorrect. File is empty!\n", filename);
		if(flock(fp, LOCK_UN) == -1)
			printf("Error: %d\n", errno);
		close(fp);
		return -1;
	}
	
	/*Check the rest of the file*/
	for(n = 1; read(fp, aux, 10) != 0; n++){
		if(strcmp(aux, _string[i]) != 0){
			/*If line doesn't match, return -1*/
			printf("%s -> Incorrect. Line %d is different: %s\n", filename, n+1, aux);
			if(flock(fp, LOCK_UN) == -1)
				printf("Error: %d\n", errno);
			close(fp);
			return -1;
		}
	}

	/*Free lock*/ 
	if(flock(fp, LOCK_UN) == -1){
		printf("%d\n", errno);
		close(fp);
		return -1;
	}
	
	/*If the number of lines left is wrong, return -1*/
	if(n != 1024){
		printf("%s -> Incorrect. Number of Lines: %d\n", filename, n);
		close(fp);
		return -1;
	}

	/*If file is ok, return 0*/
	printf("%s -> Correct\n", filename);
	close(fp);
	return 0;
}

