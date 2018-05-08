#ifndef STAMPA
#define STAMPA

#include <stdio.h>
#include <stdlib.h>

/*stampa l'introduzione al gioco*/
void stampa_intro();

/*stampa il logo*/
void stampa_logo();

/*stampa messaggio di vincita*/
void stampa_vincita();

/*stampa messaggio di perdita*/
void stampa_perdita();

/*stampa parte sopra della tabella*/
void stampa_sopra(int n_colonne);

/*stampa una riga della tabella*/
void stampa_riga(int n_colonne);

/*stampa la parte sotto della tabella*/
void stampa_sotto(int n_colonne);

/*pulisce lo schermo*/
void CLS();

/*stampa la tabella di gioco*/
void stampa(cella *array,int dim1,int dim2, int risp);

#endif