#ifndef DEFINIZIONI
#define DEFINIZIONI

#include <stdio.h>
#include <stdlib.h>

/*definizioni dei colori in ANSI*/
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"


/*
stato : assume valori compresi tra -1 e 8. (0 : vuota, -1: bomba, 1-8 : numero di bombe adiacenti)
bandiera : assume valori 0 o 1, in base a se è stata posizionata una bandierina oppure no in quella casella
seleziona: 0 se la casella non è stata selezionata, 1 altrimenti
*/

struct cell{
	int bandiera;
	int seleziona;
	int stato;
};
typedef struct cell* cella;

/*definizio del tipo struct mossa, che servirà ad implementare lo stack per la redo delle mosse
contiene x e y della casella selezionata*/
struct mossa{
	int x;
	int y;
};
typedef struct mossa mosse;

#endif
