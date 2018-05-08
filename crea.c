#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "definizioni.h"
#include "crea.h"

/*aumento di uno il valore all'interno delle caselle circostanti alla bomba*/
void aumenta(cella *array,int i,int j,int dim1, int dim2)
{
	
	if(i>0){
		if(array[i-1][j].stato!=-1)
			array[i-1][j].stato+=1;
		if(j>0){
			if(array[i-1][j-1].stato!=-1)
				array[i-1][j-1].stato+=1;
		}
		if(j<dim2-1){
			if(array[i-1][j+1].stato!=-1)
				array[i-1][j+1].stato+=1;
		}
	}
	if(i<dim1-1){
		if(array[i+1][j].stato!=-1)
			array[i+1][j].stato+=1;
		if(j<dim2-1){
			if(array[i+1][j+1].stato!=-1)
				array[i+1][j+1].stato+=1;
		}
		if(j>0){
		if(array[i+1][j-1].stato!=-1)
			array[i+1][j-1].stato+=1;
		}
	}
	if(j<dim2-1){
		if(array[i][j+1].stato!=-1)
			array[i][j+1].stato+=1;
	}
	if(j>0){
		if(array[i][j-1].stato!=-1)
			array[i][j-1].stato+=1;
	}
}


/*
******************************************************************
*---------------INIZIO PARTE "CREA"------------------------------*
******************************************************************
*/

/*richiede all'utente i dati per generare la partita*/
cella* crea(cella *arrays,int *dim1,int *dim2,int *n_bombe,int *n_mosse){
	int n_celle;
	/*chiedo all'utente i dati per creare lo schema di gico*/
	do{
	printf("➤ Inserisci numero di righe\n");
	scanf("%d",dim1);
	printf("➤ Inserisci numero di colonne\n");
	scanf("%d",dim2);
		if(*dim1<=1 || *dim2<*dim1){
			printf(ANSI_COLOR_RED "numero di righe e colonne non valido\nscegli di nuovo\n" ANSI_COLOR_RESET);
		}
	}while(*dim1<=1 || *dim2<=1 || *dim1 > 100 || *dim2 > 100);
	n_celle=(*dim1)*(*dim2);
	/*chiedo all'utente il numero delle bombe*/
	do{
		printf("➤ Inserisci numero di bombe compreso tra 1 e %d\n",n_celle-1);
		scanf("%d",n_bombe);
		if(*n_bombe<1 || *n_bombe>n_celle-1){
			printf("Numero di bombe non valido\n");
		}
	}while(*n_bombe<1 || *n_bombe>n_celle-1);
	*n_mosse=n_celle-(*n_bombe);
	/*creo lo schema iniziale di gioco*/
	arrays=crea_schema(*dim1,*dim2,*n_bombe);
	return arrays;
}

/*funzione che crea lo schema di gioco*/
cella* crea_schema(int dim1,int dim2,int n_bombe)
 {
 	FILE *f;
 	int i,j;
 	cella *array=(cella*)malloc(sizeof(cella)*dim1);
 	srand(time(NULL));
 	/*apro il file di output e stampo le dimensioni*/
 	f=fopen("input.txt","w");
 	if(f==NULL){
		printf("\nErrore\n");
	}
	else{
		fprintf(f,"%d, %d\n",dim1,dim2);
		fprintf(f,"\n");
	}
 	/*creo la matrice del campo di gioco*/
 	if(array){
	 	for(i=0;i<dim1;i++)
	 	{
	 		array[i]=(cella)malloc(sizeof(struct cell)*dim2);
	 	}
	 	for(i=0;i<dim1;i++){
	 		for (j=0;j<dim2;j++)
	 		{
	 			array[i][j].bandiera=0;
	 			array[i][j].seleziona=0;
	 			array[i][j].stato=0;
	 		}
	 	}
	 	/*genero le bombe nella matrice con la random*/
	 	while(n_bombe!=0)
	 	{
	 		i=rand()%dim1;
	 		j=rand()%dim2;
	 		while(array[i][j].stato==-1){
		 		i=rand()%dim1;
		 		j=rand()%dim2;
		 	}
		 	array[i][j].stato=-1;
			n_bombe--;
	 	}
	 	/*aumento di uno le caselle circostanti alla bomba*/
	 	for(i=0;i<dim1;i++)
		{
			for(j=0;j<dim2;j++){
				if(array[i][j].stato==-1){
				aumenta(array,i,j,dim1,dim2);
				fprintf(f,"%d, %d\n",i,j);/*<-stampo su input.txt lo schema;*/
				}
			}
	 	}
	 	fclose (f);
		return array;
	}
	else return NULL;
 }

 /*
******************************************************************
*---------------FINE PARTE "CREA"--------------------------------*
******************************************************************
*/

 /*
******************************************************************
*---------------INIZIO PARTE "LEGGI"-----------------------------*
******************************************************************
*/
 /*seleziona lo schema di gioco da file input*/
cella* leggi(cella *arrays,int *dim1,int *dim2,int *n_bombe,int *n_mosse)
{
		/*apro il file di input*/
		
		FILE *f;
		int seleziona,n_celle;
		/*chiedo all'utente quale campo di gioco pre esistente vuole utilizzare*/
		do{
			printf("➤ Scegli la modalità\n👉 Premi 1 per facile\n👉 Premi 2 per medio\n👉 Premi 3 per difficile\n👉 Premi 4 per lo schema creato\n");
			scanf("%d",&seleziona);
			if(seleziona<1 || seleziona>4 ){
				printf("\nErrore selezione non valida\n");
			}
		}while(seleziona<1 || seleziona>4);
		if(seleziona==1){
			f=fopen("facile.txt","a");
			fprintf(f,"\n");
			fclose(f);
			f=fopen("facile.txt","r");
		}
		else if(seleziona==2){
			f=fopen("medio.txt","a");
			fprintf(f,"\n");
			fclose(f);
			f=fopen("medio.txt","r");
		}
		else if(seleziona==3){
			f=fopen("difficile.txt","a");
			fprintf(f,"\n");
			fclose(f);
			f=fopen("difficile.txt","r");
		}
		else if(seleziona==4){
			f=fopen("input.txt","a");
			fprintf(f,"\n");
			fclose(f);
			f=fopen("input.txt","r");
		}
		if(f==NULL){
			printf("\nErrore file non trovato\n");
		}
		else{
			/*leggo il campo di gioco dal file di input prescelto e creo la partita*/
			arrays=leggi_schema(f,dim1,dim2,n_bombe);
			n_celle=(*dim1)*(*dim2);	
			*n_mosse=n_celle-*n_bombe;
		}
		fclose(f);
		return arrays;
}

/*creo il campo di gioco in base allo schema scelto*/
cella* leggi_schema(FILE *f, int *rig, int *col,int *n_bombe)
{
	cella *array;
	int i,j;
	int dim1,dim2;
	fscanf(f,"%d, %d",&dim1,&dim2);
	*rig=dim1;
	*col=dim2;

	array=(cella*)malloc(sizeof(cella)*dim1);
	/*creo la matrice del campo di gioco*/
	if(array){
	 	for(i=0;i<dim1;i++){
	 		array[i]=(cella)malloc(sizeof(struct cell)*dim2);
	 	}
	 	for(i=0;i<dim1;i++){
	 		for (j=0;j<dim2;j++)
	 		{
	 			array[i][j].bandiera=0;
	 			array[i][j].seleziona=0;
	 			array[i][j].stato=0;
	 		}
	 	}
	 	/*genero le bombe nella matrice leggendo le posizioni dal file di input*/
	 	while( fscanf(f,"%d, %d",&i,&j)  && !feof(f))
		{
		 	array[i][j].stato=-1;
		 	*n_bombe+=1;
	 	}
	 	/*aumento di uno le caselle circostanti alla bomba*/
	 	for(i=0;i<dim1;i++)
		{
			for(j=0;j<dim2;j++){
				if(array[i][j].stato==-1){
				aumenta(array,i,j,dim1,dim2);
				}
			}
	 	}
		return array;
	}
	else return NULL;
}

/*
******************************************************************
*---------------FINE PARTE "LEGGI"-------------------------------*
******************************************************************
*/