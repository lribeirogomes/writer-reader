make: clear .o .exe clean

clear:
	clear

.o: escritor.c escritor_c.c leitor1.c leitor1_c.c leitor2.c leitor3.c def.h
	gcc -c -Wall -pedantic -ansi escritor.c
	gcc -c -Wall -pedantic -ansi escritor_c.c
	gcc -c -Wall -pedantic -ansi leitor1.c
	gcc -c -Wall -pedantic -ansi leitor1_c.c
	gcc -c -Wall -pedantic -ansi leitor2.c
	gcc -c -Wall -pedantic -ansi leitor3.c

.exe: .o
	gcc escritor.o -o escritor
	gcc escritor_c.o -o escritor_c
	gcc leitor1.o -o leitor1
	gcc leitor1_c.o -o leitor1_c
	gcc leitor2.o -lpthread -o leitor2
	gcc leitor3.o -lpthread -o leitor3

clean:
	rm *.o
