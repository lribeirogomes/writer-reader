make: clear .o .exe clean

clear:
	clear

.o: escritor.c leitor.c copiador.c def.h
	gcc -c -Wall -pedantic -ansi escritor.c
	gcc -c -Wall -pedantic -ansi escritor_c.c
	gcc -c -Wall -pedantic -ansi leitor.c
	gcc -c -Wall -pedantic -ansi copiador.c

.exe: .o
	gcc escritor.o -o escritor
	gcc escritor_c.o -o escritor_c
	gcc leitor.o -o leitor
	gcc copiador.o -o copiador
	
clean:
	rm *.o
