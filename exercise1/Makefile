make: clear .o .exe clean

clear:
	clear

.o: escritor.c leitor.c
	gcc -c -Wall -pedantic -ansi escritor.c
	gcc -c -Wall -pedantic -ansi leitor.c

.exe: escritor.o leitor.o
	gcc escritor.o -o escritor
	gcc leitor.o -o leitor
	
clean:
	rm *.o
