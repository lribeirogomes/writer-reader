make: clear .o .exe clean

clear:
	clear

.o: escritor.c leitor.c monitor.c def.h
	gcc -c -Wall -pedantic escritor.c
	gcc -c -Wall -pedantic leitor.c
	gcc -c -Wall -pedantic monitor.c

.exe: escritor.o leitor.o monitor.o
	gcc escritor.o -lpthread -o escritor
	gcc leitor.o -lpthread -o leitor
	gcc monitor.o -o monitor
	
clean:
	rm *.o
