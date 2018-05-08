#ifndef CREA
#define CREA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*aumento di uno le caselle circostanti alla bomba*/
void aumenta(cella *array,int i,int j,int dim1, int dim2);

/*chiedo all'utente i dati*/
cella* crea(cella *arrays,int *dim1,int *dim2,int *n_bombe,int *n_mosse);

/*crea lo schema di gioco*/
cella* crea_schema(int dim1,int dim2,int n_bombe);

/*legge lo schema di gioco da file*/
cella* leggi(cella *arrays,int *dim1,int *dim2,int *n_bombe,int *n_mosse);

/*crea lo schema di gioco da file letto*/
cella* leggi_schema(FILE *f, int *rig, int *col,int *n_bombe);

#endif