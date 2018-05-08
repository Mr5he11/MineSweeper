#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "definizioni.h"
#include "gioca.h"
#include "stampa.h"
#include "mosse.h"

/*funzione per l'attuazione di una mossa*/
int gioca(cella *arrays,int dim1, int dim2,int *risp,int *n_mosse,int *redo,mosse *stack,int *top,int *redo_max)
{
	int mossa;
	mosse m;
	/*dico all'utente il numero di mosse ancora disponibili*/
	printf("\n\n♥ Hai ancora %d annulla mossa disponibili\n\n",*redo_max);
	/*chiedo all'utente il tipo di mossa da eseguire*/
	do{
		printf("👉  Premi 1 per liberare la casella\n👉  Premi 2 per inserire bandierina\n👉  Premi 3 per rimuovere la bandierina\n👉  Premi 4 per COMINCIARE UNA NUOVA PARTITA\n👉  Premi 0 per USCIRE\n");
		scanf("%d",&mossa);
		if(mossa<0 || mossa>4){
			printf(ANSI_COLOR_RED "selezione non valida\nscegli di nuovo\n" ANSI_COLOR_RESET);
		}
	}while(mossa<0 || mossa>4);
	/*se la mossa è valida chiedo all'utente riga e colonna della casella in cui inserire la mossa*/
	if (mossa > 0 && mossa < 4){
		do{
			printf("➤ Inserisci la riga della casella\n");
			scanf("%d",&m.x);
			if(m.x<0 || m.x>dim1-1){
				printf(ANSI_COLOR_RED "Riga non valida reinserisci riga\n" ANSI_COLOR_RESET);
			}
		}while(m.x<0 || m.x>dim1-1);
		do{
			printf("➤ Inserisci la colonna della casella\n");
			scanf("%d",&m.y);
			if(m.x<0 || m.x>dim1-1){
				printf(ANSI_COLOR_RED "colonna non valida, reinserisci riga\n" ANSI_COLOR_RESET);
			}
		}while(m.y<0 || m.y>dim2-1);
		/*se vuole liberare la casella*/
		if(mossa==1){
			*risp=inserisci_mossa(arrays,stack,m,top,n_mosse,dim1,dim2);
			if(*risp==4){
				(*redo_max)--;
			}
			if(*risp==0){
				printf(ANSI_COLOR_RED "Mossa non valida casella gi\224 usata\nreinserisci mossa\n" ANSI_COLOR_RESET);
				sleep(2);
			}
		}
		/*se vuole mettere una bandierina*/
		else if(mossa==2){
			if(arrays[m.x][m.y].seleziona==0){
				arrays[m.x][m.y].seleziona=1;
				arrays[m.x][m.y].bandiera=1;
			}
			else{
				*risp=0;
				if(arrays[m.x][m.y].bandiera==1){
					printf(ANSI_COLOR_RED "Mossa non valida bandierina gi\224 presente\nreinserisci mossa\n" ANSI_COLOR_RESET);
					sleep(2);
				}
				else{
					printf(ANSI_COLOR_RED "Mossa non valida casella gi\224 usata\nreinserisci mossa\n" ANSI_COLOR_RESET);
					sleep(2);
				}
			}
		}
		/*se vuole togliere una bandierina*/
		else if(mossa==3){
			if(arrays[m.x][m.y].bandiera==0)
			{
				*risp=0;
				printf(ANSI_COLOR_RED "Mossa non valida bandierina non presente\nreinserisci mossa\n" ANSI_COLOR_RESET);
				sleep(2);
			}else{
				arrays[m.x][m.y].bandiera=0;
				arrays[m.x][m.y].seleziona=0;
			}
		}
		/*se l'utente ha beccato una bomba e ha ancora la possibilità di tornare indietro*/
		if(*risp==4 && *redo_max>-1){
			CLS();
			stampa(arrays,dim1,dim2,*risp);
			do{
				printf("Hai preso una bomba!\n👉 Premi 1 per anullare la mossa\n");
				scanf("%d",&mossa);
				if(mossa<1 || mossa>2 ){
					printf(ANSI_COLOR_RED "Mossa non valida scegli di nuovo\n" ANSI_COLOR_RESET);
				}
			}while(mossa<1 || mossa>2 );
			/*se l'utente sceglie di tornare indietro*/
			if(mossa==1){
				int i = 0;
				(*redo)++;
				while(i < *redo && *top > 0){
					annulla_mossa(arrays, stack, top, n_mosse);
					i++;
				}
				*risp=1;
			}
		}
		/*se  l'utente ha finito le possibilità di tornare indietro*/
		else if(*redo_max==-1){
			*risp=3;
			printf("     HAI PERSO\n");
		}
		/*se è stato eseguito un annulla mossa oppure se si ha perso*/
		return 1;
		/*se l'utente sceglie di uscire dal gioco*/
	}else if (mossa == 0){
		return 0;
		/*se si vuole tornare al menu principale*/
	}else{
		return 2;
	}	
}