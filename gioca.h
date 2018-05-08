#ifndef GIOCA
#define GIOCA

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*funzione per l'attuazione di una mossa*/
int gioca(cella *arrays,int dim1, int dim2,int *risp,int *n_mosse,int *redo,mosse *stack,int *top,int *redo_max);

#endif