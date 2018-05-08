#ifndef MOSSE
#define MOSSE

#include <stdio.h>
#include <stdlib.h>

/*funzione per l'inserimento di una mossa dello stack*/
int push(mosse stack[], int *ptop, mosse elem, int dim);

/*funzione per la rimozione di una mossa dallo stack
NB: le informazioni riguardanti la mossa prelevata vengono salvate in *pitem */
int pop(mosse stack[], int *ptop, mosse *pitem);

/*funzione che controlla i confini*/
int confini(mosse m, int dim1, int dim2);

/*funzione ricorsiva per selezionare tutte le caselle adiacenti ad una casella vuota data - implementazione ricorsiva*/
int seleziona(cella vet[], mosse stack[], int *ptop, mosse new, int dim1, int dim2, int *n_mosse);

/*funzione per l'esecuzione di una mossa*/
int inserisci_mossa(cella *vet, mosse stack[], mosse new, int *ptop, int *n_mosse, int dim1, int dim2);

/*funzione per l'annullamento di una mossa*/
/*per fare in modo che si prelevino tutti i record necessari si prelevano informazioni dallo stack fino a quando non si trova un record con x<0*/
/*x<0 codifica la fine delle conseguenze di una data mossa. Quando si fa una mossa all'interno dello stack viene inserito questo record particolare.*/
int annulla_mossa(cella vet[], mosse stack[], int *ptop, int *n_mosse);

#endif