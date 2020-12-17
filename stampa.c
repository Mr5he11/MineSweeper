#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "definizioni.h"
#include "stampa.h"


/*stampo il logo del gioco*/
void stampa_logo(){
	printf("╔═════════════════════════════════════════════════════════════════╗\n");
	printf("║ ╔═══╗╔═══╗╔═╗╔═╗╔═══╗╔═══╗     ╔═╗╔═╗╔══╗╔═╗ ╔╗╔═══╗╔════╗╔═══╗ ║\n");
	printf("║ ║╔═╗║║╔═╗║║ ╚╝ ║║╔═╗║║╔═╗║     ║ ╚╝ ║╚╣╠╝║ ╚╗║║║╔═╗║║╔╗╔╗║║╔═╗║ ║\n");
	printf("║ ║║ ╚╝║║ ║║║╠╗╔╣║║╚═╝║║║ ║║     ║╠╗╔╣║ ║║ ║╔╗╚╣║║║ ║║╚╝║║╚╝║║ ║║ ║\n");		
	printf("║ ║║ ╔╗║╚═╝║║║║║║║║╔══╝║║ ║║     ║║║║║║ ║║ ║║╚╗║║║╚═╝║  ║║  ║║ ║║ ║\n");
	printf("║ ║╚═╝║║╔═╗║║║║║║║║║   ║╚═╝║     ║║║║║║╔╣╠╗║║ ║ ║║╔═╗║  ║║  ║╚═╝║ ║\n");
	printf("║ ╚═══╝╚╝ ╚╝╚╝╚╝╚╝╚╝   ╚═══╝     ╚╝╚╝╚╝╚══╝╚╝ ╚═╝╚╝ ╚╝  ╚╝  ╚═══╝ ║\n");
	printf("╚═════════════════════════════════════════════════════════════════╝\n\n\n");
}
/*stampo le istruzioni iniziali*/
void stampa_intro(){
	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("+ Benvenuto in \"CAMPO MINATO\"! Prima di iniziare a   +\n");
	printf("+ giocare ti sarà richiesto di inserire alcuni dati  +\n");
	printf("+ quali le dimensioni del campo, il numero di bombe  +\n");
	printf("+ e il numero di volte in cui avrai la possibilità   +\n");
	printf("+ di annullare la mossa. Ricorda che le dimensioni   +\n");
	printf("+ del campo consigliate sono minori di 50x50 e che   +\n");
	printf("+ il numero di bombe non può essere 0 o maggiore     +\n");
	printf("+ del numero di caselle. Per il resto segui le       +\n");
	printf("+ indicazioni del programma. Buon divertimento!      +\n");
	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
}

/*stampo in caso di vittoria*/
void stampa_vincita(){
	printf("█ █ █▀█ █    █ █ █ █ █ ▀█▀ █▀█\n");
	printf("█▀█ █▀█ █    █ █ █ █▚█  █  █ █\n");
	printf("▀ ▀ ▀ ▀ ▀     ▀  ▀ ▀ ▀  ▀  ▀▀▀\n");
	printf("▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬\n\n");
}

/*stampo in caso di perdita*/
void stampa_perdita(){
	printf("█ █ █▀█ █    █▀█ █▀▀ █▀▄ █▀▀ █▀█\n");
	printf("█▀█ █▀█ █    █▀▀ █▀▀ ██▀  ▀▄ █ █\n");
	printf("▀ ▀ ▀ ▀ ▀    ▀   ▀▀▀ ▀ ▀ ▀▀▀ ▀▀▀\n");
	printf("▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬\n");
}


/*stampo i contorni del campo*/
void stampa_sopra(int n_colonne){
	int i;
	printf("   ┌───");
	for(i = 1; i < n_colonne; i++){
		printf("┬───");
	}
	printf("┐\n");
}

void stampa_riga(int n_colonne){
	int i;
	printf("   ├───");
	for(i = 1; i < n_colonne; i++){
		printf("┼───");
	}
	printf("┤\n");
}

void stampa_sotto(int n_colonne){
	int i;
	printf("   └───");
	for(i = 1; i < n_colonne; i++){
		printf("┴───");
	}
	printf("┘\n");
}

/*pulisco il terminale in caso di windows o ubuntu*/
void CLS(){
	int command = system("clear");
	if (command){
		system("CLS");
	}
}

/*stampo lo schema di gioco*/
void stampa(cella *array,int dim1,int dim2, int risp)
{
	
	int i,j;
	stampa_logo();
	stampa_sopra(dim2);
	for(i=0;i<(dim1);i++){
		/*stampo i numeri delle righe*/
		if (i <10){
			printf("%d  │",i);
		}else{
			printf("%d │",i);
		}
		
		for(j=0;j<dim2;j++){
			/*se l'utente ha perso scopro tutto il campo*/
			if(risp==3){
				array[i][j].seleziona=1;
			}
			/*se l'utente ha vinto*/
			else if(risp==5){
				/*dove c'è la bomba metto le bandierine*/
				if(array[i][j].stato==-1){
					array[i][j].seleziona=1;
					array[i][j].bandiera=1;
				}
			}
			/*stampo il campo normalmente*/
			if(array[i][j].seleziona==1){
				if(array[i][j].bandiera==1 && risp!=4){
					printf(" ⚐ │");
				}
				else{
					if(array[i][j].stato==-1){
						if (array[i][j].bandiera==1){
							printf(" ⚐ │");
						}else{
							printf("💣 │");
						}
					}
					else if(array[i][j].stato==0){
						printf(" %c │",' ');
					}
					else{
						if (array[i][j].bandiera){
							printf(" ⚐ │");
						}else{
							printf(" %d │",array[i][j].stato);
						}
					}
				}
			}
			else
				printf(" ▇ │");	
		}
		printf("\n");
		if (i == (dim1-1)){
			stampa_sotto(dim2);
		}else{
			stampa_riga(dim2);
		}
	}
	printf("    ");
	/*stampo i numeri delle colonne*/
	for(j=0;j<dim2;j++){
		if (j < 10){
			printf(" %d  ",j);
		}else{
			printf(" %d ",j);
		}
		
	}
	printf("\n");
	/*se l'utente vince stampa la vittoria*/
	if(risp==5){
		printf("\n");
		stampa_vincita();
		printf("\n");
	}
}