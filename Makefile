game: main.o gioca.o stampa.o mosse.o crea.o
	gcc -std=gnu89 -Wall -pedantic main.o gioca.o stampa.o mosse.o crea.o -o campominato

main.o: main.c gioca.h stampa.h mosse.h crea.h definizioni.h
	gcc -std=gnu89 -Wall -pedantic -c main.c -o main.o

gioca.o: gioca.c gioca.h stampa.h mosse.h definizioni.h
	gcc -std=gnu89 -Wall -pedantic -c gioca.c -o gioca.o

stampa.o: stampa.c stampa.h definizioni.h
	gcc -std=gnu89 -Wall -pedantic -c stampa.c -o stampa.o

crea.o: crea.c crea.h definizioni.h
	gcc -std=gnu89 -Wall -pedantic -c crea.c -o crea.o

mosse.o: mosse.c mosse.h definizioni.h
	gcc -std=gnu89 -Wall -pedantic -c mosse.c -o mosse.o

clean: 
	rm -f *.o
	rm -f game
