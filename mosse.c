#include <stdio.h>
#include <stdlib.h>
#include "definizioni.h"
#include "mosse.h"

/*funzione per l'inserimento di una mossa dello stack, ptop è puntatore alla testa dello stack*/
int push(mosse stack[], int *ptop, mosse elem, int dim){
	if (*ptop < dim){
		stack[*ptop] = elem;
		(*ptop)++; 
		return 1;
	}else{
		return 0;
	}
}

/*funzione per la rimozione di una mossa dallo stack
NB: le informazioni riguardanti la mossa prelevata vengono salvate in *pitem */
int pop(mosse stack[], int *ptop, mosse *pitem){
	if (*ptop > 0){
		(*ptop)--;
		*pitem = stack[*ptop];
		return 1;
	}else{
		return 0;
	}
}

/*funzione che controlla i confini*/
int confini(mosse m, int dim1, int dim2){
	if (m.x < dim1 && m.x >= 0 && m.y < dim2 && m.y >= 0){
		return 1;
	}else{
		return 0;
	}
}

/*funzione ricorsiva per selezionare tutte le caselle adiacenti ad una casella vuota data - implementazione ricorsiva*/
int seleziona(cella vet[], mosse stack[], int *ptop, mosse new, int dim1, int dim2, int *n_mosse){
	int i = new.x;
	int j = new.y;
	int dim = dim1*dim2*2;
	if (!confini(new, dim1, dim2)){
		return -1; /*errore per i confini*/
	}else{
		if (vet[i][j].stato > 0){
			if (vet[i][j].seleziona == 1){
				return -2; /*errore per la selezione*/
			}else{
				vet[i][j].seleziona = 1;
				push(stack, ptop, new, dim);
				(*n_mosse)--;
				return 1; /*successo selezione caso numero*/
			}
		}else{
			if (vet[i][j].seleziona == 1){
				return -3; /*errore per la selezione - vuoto*/
			}else{
				mosse m1;
				mosse m2;
				mosse m3;
				mosse m4;
				mosse m5;
				mosse m6;
				mosse m7;
				mosse m8;
				m1.x = i + 1;
				m1.y = j;
				m2.x = i - 1;
				m2.y = j;
				m3.x = i;
				m3.y = j + 1;
				m4.x = i;
				m4.y = j - 1;
				m5.x = i + 1;
				m5.y = j + 1;
				m6.x = i - 1;
				m6.y = j - 1;
				m7.x = i - 1;
				m7.y = j + 1;
				m8.x = i + 1;
				m8.y = j - 1;
				vet[i][j].seleziona = 1;
				push(stack, ptop, new, dim);
				(*n_mosse)--;
				seleziona(vet, stack, ptop, m1, dim1, dim2, n_mosse);
				seleziona(vet, stack, ptop, m2, dim1, dim2, n_mosse);
				seleziona(vet, stack, ptop, m3, dim1, dim2, n_mosse);
				seleziona(vet, stack, ptop, m4, dim1, dim2, n_mosse);
				seleziona(vet, stack, ptop, m5, dim1, dim2, n_mosse);
				seleziona(vet, stack, ptop, m6, dim1, dim2, n_mosse);
				seleziona(vet, stack, ptop, m7, dim1, dim2, n_mosse);
				seleziona(vet, stack, ptop, m8, dim1, dim2, n_mosse);
				return 0; /*successo selezione - vuoto*/
			}
		}
	}
}

/*funzione per l'esecuzione di una mossa*/
int inserisci_mossa(cella *vet, mosse stack[], mosse new, int *ptop, int *n_mosse, int dim1, int dim2){
	int i=new.x;
	int j=new.y;
	int n_celle = dim1*dim2*2;
	mosse end;
	end.x = -1;
	end.y = -1;
	if(vet[i][j].seleziona==0){
		if(vet[i][j].stato==-1 || (vet[i][j].stato >0 && vet[i][j].stato < 9)){
			int r, s;
			vet[i][j].seleziona=1;
			(*n_mosse)--;
			r = push(stack, ptop, end, n_celle);
			s = push(stack, ptop, new, n_celle);
			if (r && s && vet[i][j].stato==-1){
				return 4;
			}else{
				if (r && s && vet[i][j].stato>0){
					return 1;
				}else{
					return 1;
				}
			}
		}else{
			int r = push(stack, ptop, end, n_celle);
			int s = seleziona(vet, stack, ptop, new, dim1, dim2, n_mosse);
			if (!r || !s){
				return -10;
			}else{
				return 1;
			}
		}		
		return 1;
	}
	else return 0;
}

/*funzione per l'annullamento di una mossa*/
/*per fare in modo che si prelevino tutti i record necessari si prelevano informazioni dallo stack fino a quando non si trova un record con x<0*/
/*x<0 codifica la fine delle conseguenze di una data mossa. Quando si fa una mossa all'interno dello stack viene inserito questo record particolare.*/
int annulla_mossa(cella vet[], mosse stack[], int *ptop, int *n_mosse){
	mosse corrente;
	int end = 0;
	corrente.x = 0;
	corrente.y = 0;
	do{
		int x = pop(stack, ptop, &corrente);
		if (x == 1){
			int i = corrente.x;
			int j = corrente.y;
			if (i >= 0){
				vet[i][j].seleziona = 0;
				(*n_mosse)++;
			}else{
				end = 1;
			}
		}
	}while(!end);
	return 0;
}

