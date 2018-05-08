--- READM ME ---

Compilare col seguente comando:
	"make game"

Eseguire col comando:
	"./campominato"

Per il funzionamento si suppone che l'utente inserisca solamente dati numerici ogni qualvolta essi vengano richiesti.
Gli schemi di gioco creati dall'utente vengono salvati nel file "input.txt", le quali informazioni verrano lette per caricare il medesimo in una partita successiva.

Il pacchetto contiene un file makefile per la corretta compilazione,
i seguenti file .c :
	- mane.c
	- gioca.c (contiene la funzione per giocare)
	- crea.c (contiene le funzioni per creare e caricare un campo)
	- mosse.c (implementazione delle strutture dati per le singole mosse)
	- stampa.c (funzioni per la stampa)

ed i relativi file  .h

BUG conosciuti:
	se nei campi numerici si inserisce una lettera il programma va in loop
	