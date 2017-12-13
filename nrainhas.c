#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
struct Linha{
	int i, j, k;
	struct Linha *proximo, *anterior;
};

struct Rainhas{
	int y, x, check;
};

static int TAM;
int cont = 0;
char **tabuleiro;
int rainhas = 0;
struct Rainhas *r;
int ok = 1;

void preencher(int i, int j) {
	tabuleiro[i][j] = 'R';
	int k = 1;
	while(i+k < TAM){
		tabuleiro[i+k][j] = 'x';
		k++;
	}
	k=1;
	while(j+k < TAM){
		tabuleiro[i][j+k] = 'x';
		k++;
	}
	k=1;
	while(i-k >= 0){
		tabuleiro[i-k][j] = 'x';
		k++;
	}
	k = 1;
	while(j-k >= 0){
		tabuleiro[i][j-k] = 'x';
		k++;
	}
	k =1;
	while(i+k < TAM && j+k < TAM){
		tabuleiro[i+k][j+k] = 'x';
		k++;
	}
	k = 1;
	while(i-k >= 0 && j-k >= 0){
		tabuleiro[i-k][j-k] = 'x';
		k++;
	}
	k=1;
	while(i + k < TAM && j-k >=0){
		tabuleiro[i+k][j-k] = 'x';
		k++;
	}
	k = 1;
	while(i-k >= 0 && j+k < TAM){
		tabuleiro[i-k][j+k] = 'x';
		k++;
	}
}
void verificar() {
	for(int k = 0; k < rainhas;k++){
		preencher(r[k].x, r[k].y);
	}
}
void limpar(int i, int j) {
	tabuleiro[i][j] = '_';
	int k = 1;
	while(i+k < TAM){
		tabuleiro[i+k][j] = '_';
		k++;
	}
	k=1;
	while(j+k < TAM){
		tabuleiro[i][j+k] = '_';
		k++;
	}
	k=1;
	while(i-k >= 0){
		tabuleiro[i-k][j] = '_';
		k++;
	}
	k = 1;
	while(j-k >= 0){
		tabuleiro[i][j-k] = '_';
		k++;
	}
	k =1;
	while(i+k < TAM && j+k < TAM){
		tabuleiro[i+k][j+k] = '_';
		k++;
	}
	k = 1;
	while(i-k >= 0 && j-k >= 0){
		tabuleiro[i-k][j-k] = '_';
		k++;
	}
	k=1;
	while(i + k < TAM && j-k >=0){
		tabuleiro[i+k][j-k] = '_';
		k++;
	}
	k = 1;
	while(i-k >= 0 && j+k < TAM){
		tabuleiro[i-k][j+k] = '_';
		k++;
	}
}
void printar() {
	for(int i = 0; i < TAM;i++){
		for(int j = 0; j < TAM;j++){
			printf("%c ", tabuleiro[i][j]);
		}
		printf("\n");
	}
	printf("============================================\n");
}

void zerar(){
	int i = 0, j = 0;
	for(i = 0;i < TAM;i++){
		for(j = 0;j < TAM;j++){
			tabuleiro[i][j] = '_';
		}
	}
}

int procuraColuna(char *linha, int k) {
	for(int i = k;i < TAM;i++){
		if(linha[i] == '_'){
			return i;
		}
	}
	return -1;
}

void Start(struct Linha *l){
	while(l->proximo != NULL)
		l = l->proximo;
	l->k = l->j;
	if(l->i < TAM){
		l->j = procuraColuna(tabuleiro[l->i], l->k);
		if(l->j == l->k){
			if(!ok && !r[rainhas].check)
				l->j = procuraColuna(tabuleiro[l->i],(l->k)+1);
			if(l->j == 0 && l->i == 0 && !ok) 
				l->j = 1;
			if(rainhas < TAM && r[rainhas].x != -1){
				if(r[rainhas].x == l->i && r[rainhas].y == l->j && !r[rainhas].check)
					l->j = procuraColuna(tabuleiro[l->i],(l->k));
				if(r[rainhas].x == 0 && r[rainhas].y == TAM-1)
					l->j = 0;
				r[rainhas].check = 1;
			}
			if(l->i == 0 && l->j < l->k && l->k == TAM-1 && tabuleiro[l->i][0] != 'x'){
				l->j = 0;
				exit(0);
			}
		}
		ok = 0;
		if(l->j != -1){
			r[rainhas].x = l->i;
			r[rainhas++].y = l->j;
			preencher(l->i, l->j);
			struct Linha *l2 = malloc(sizeof(struct Linha));
			l2->i = (l->i)+1;
			l2->j = 0;
			l2->k = 0;
			l->proximo = l2;
			l2->anterior = l;
			//printar();

		}else{
			struct Linha *anterior = l->anterior;
			anterior->proximo = NULL;
			l->anterior = NULL;
			limpar(r[rainhas-1].x, r[rainhas-1].y);
			r[rainhas-1].check = 0;
			rainhas--;
			free(l);
			verificar();
			//printar();
		}
	}else{
		struct Linha *anterior = l->anterior;
		anterior->proximo = NULL;
		l->anterior = NULL;
		//printar();
		int i;
		printf("%dº = ", ++cont);
		for(i = 0; i < TAM;i++)
			printf("%d ", r[i].y+1);
		printf("\n");
		limpar(r[rainhas-1].x, r[rainhas-1].y);
		r[rainhas-1].check = 0;
		rainhas--;
		free(l);
		verificar();
		//sleep(2);

	}
}

void main(){
	scanf("%d", &TAM);
	r = malloc(TAM*sizeof(struct Rainhas));
	tabuleiro = (char**) malloc(TAM*sizeof(char*));
	register int i;
	for(i = 0; i < TAM;i++){
		tabuleiro[i] = (char*) malloc(TAM*sizeof(char));
		r[i].x = -1;
		r[i].y = -1;
		r[i].check = 0;
	}
	struct Linha *l = malloc(sizeof(struct Linha));
	l->proximo = NULL;
	zerar();
	while(1){
		Start(l);
	}
}
