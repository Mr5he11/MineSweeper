#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "definizioni.h"
#include "gioca.h"
#include "stampa.h"
#include "mosse.h"
#include "crea.h"

/*compila con : make game*/

int main()
{
	int risp; /*flag che determina lo stato del giocatore (vincita, perdita*/
	int redo; /*contatore delle redo*/
	int redo_max; /*numero di redo possibili*/
	int seleziona; /*flag per la selezione dell'opzione dal menù iniziale*/
	int dim1, dim2; /*dimensioni della matrice*/
	int n_mosse; /*contatore delle mosse*/
	int n_bombe; /*numero di bobe*/
	int esc_from_ev; /*flag che controlla l'uscita dal programma*/
	int esc_from_low; /*flag che controlla l'uscita dal ciclo di gioco e quindi la possibilità di cominciare una nuova partita*/
	cella *arrays = NULL; /*puntatore alla matrice*/
	mosse *stack = NULL; /*puntatore all'array*/
	int top;

	/*ciclo principale, ogni iterazione rappresenta una partita*/
	while(!esc_from_ev){

		/*inizializzo variabili*/
		risp = 1;
		redo = 0;
		redo_max = 0;
		seleziona = 0;
		n_mosse = 0;
		n_bombe = 0;
		esc_from_low = 0;
		esc_from_ev = 0;
		top = 0;

		/*Se inizio una nuova partita controllo che la matrice non sia allocata. Se è allocata, libero il suo spazio in heap*/
		if (arrays){
			int i;
			for(i = 0; i < dim1; i++){
				free(arrays[i]);
			}
			free(arrays);
		}

		/*controllo che lo stack non sia allocato, se lo è libero il suo spazio in heap*/
		if(stack){
			free(stack);
		}

		/*selezione da menu con controllo dell'input*/
		do{
			CLS();
			stampa_logo();
			stampa_intro();
			printf("👉  Premi 1 per generare un nuovo schema\n👉  Premi 2 per usare uno schema esistente\n👉  Premi 3 per uscire\n");
			scanf("%d",&seleziona);
			if(seleziona<1 || seleziona>3 ){
				printf(ANSI_COLOR_RED "\nErrore: selezione non valida\n" ANSI_COLOR_RESET);
				sleep(2);
			}
		}while(seleziona<1 || seleziona>3);

		/*pulisci lo schermo e procedi*/		
		CLS();
		stampa_logo();

		/*gestione della selezione, con eventuale creazione o caricamento del campo*/
		switch (seleziona){
			case 1 : 
				arrays=crea(arrays,&dim1,&dim2,&n_bombe,&n_mosse);
				break;
			case 2 :
				arrays=leggi(arrays,&dim1,&dim2,&n_bombe,&n_mosse);
				break;
			case 3 :
				esc_from_ev = 1;
				break;
			default :
				break;
		}

		/*se il campo è stato generato correttamente*/
		if(arrays){
			
			/*chiedo in input il numero di redo massime con controllo dell'input*/
			do{
				printf("Inserisci il numero di vite\n");
				scanf("%d",&redo_max);
				if(redo_max < 0 || redo_max >= n_bombe){
					printf(ANSI_COLOR_RED "\nErrore: il numero di vite deve essere positivo\n" ANSI_COLOR_RESET);
				}
			}while(redo_max < 0);

			/*pulisco lo schermo e stampo la matrice*/
			CLS();
			stampa(arrays,dim1,dim2,1);

			/*alloco l'array per lo stack*/
			stack=(mosse*)malloc(sizeof(mosse)*(dim1*dim2)*2);
			
			/*ciclo secondario, ogni iterazione corrisponde ad una giocata*/
			while(n_mosse>0 && !esc_from_ev && !esc_from_low){

				/*controllo che non sia finito il numero di redo (significherebbe che il giocatore ha perso*/
				if(redo_max != -1){
					int ris_gioca;
					ris_gioca = gioca(arrays,dim1,dim2,&risp,&n_mosse,&redo,stack,&top,&redo_max);
					switch(ris_gioca){
						case 0 :
							esc_from_ev = 1;
							break;
						case 2 :
							esc_from_low = 1;
							break;
						default:
							break;
					}
					CLS();
				}

				/*controllo che il numero di mosse non sia uguale a 0 (in quel caso il giocatore avrebbe vinto*/
				if(n_mosse!=0 && !esc_from_ev && !esc_from_low){
					stampa(arrays,dim1,dim2,risp);
				}

				/*se redo_max == 1 allora il giocatore ha perso, stampo il messaggio di perdita e gli chiedo se vuole iniziare una nuova partita*/
				if(redo_max==-1 &&!esc_from_ev && !esc_from_low){	
					printf("\n");
					stampa_perdita();
					printf("\nPremi 0 per uscire dal gioco, qualsiasi altro numero per cominciare una nuova partita\n");
					scanf("%d",&seleziona);
					if(seleziona==0){
						esc_from_ev = 1;
					}else{
						esc_from_low = 1;
					}
				}
			}

			/*se ne esc_from_ev ne es_from_low sono affermati, significa che non si sono verificate tutte le situazioni precedenti,
			dunque il giocatore ha vinto*/
			if(!esc_from_ev && !esc_from_low){
				risp=5; /*flag che indica che il giocatore ha vinto*/
				stampa(arrays,dim1,dim2,risp);
				printf("Premi 0 per uscire dal gioco, qualsiasi altro numero per cominciare una nuova partita\n");
				scanf("%d",&seleziona);
				if(seleziona==0){
					esc_from_ev = 1;
				}
			}
		}
	}
	return EXIT_SUCCESS	;
}