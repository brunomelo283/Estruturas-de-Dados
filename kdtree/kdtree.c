#include<stdio.h>
#include<stdlib.h>
#define K 2
#define TF 6

struct kdtree
{
	int ponto[K];
	struct kdtree  *esq, *dir;
};
typedef struct kdtree kdTree;


kdTree *CriaNo(int ponto[K])
{
	int i;
	kdTree *nodo = (kdTree*)malloc(sizeof(kdTree));
	for(i=0; i < K; i++)
	{
		nodo->ponto[i] = ponto[i];
	}
	nodo->esq = nodo->dir = NULL;
	return nodo;
}


void insereR(kdTree **raiz, int ponto[], int n)
{
	int d;
	if(*raiz == NULL)
		*raiz = CriaNo(ponto);
	else
	{
		d = n % K;
		if(ponto[d] < (*raiz)->ponto[d])
			insereR(&(*raiz)->esq, ponto, n+1);
		else
			insereR(&(*raiz)->dir, ponto, n+1);
	}
}

void exibir(kdTree *t, int x, int y, int dist)
{
	int i;
	if(t != NULL)
	{
		gotoxy(x, y);
		for(i=0; i<K;i++)
			printf("[%d]", t->ponto[i]);
		y++;
		if(t->esq != NULL)
			gotoxy(x- dist/2,y), printf("/");	
		exibir(t->esq, x-dist, y+1, dist/2);
		if(t->dir != NULL)
			gotoxy(x+dist/2, y), printf("\\");		
		exibir(t->dir, x+dist, y+1, dist/2);
	}
}


int main(void)
{
	kdTree *raiz = NULL;
	int i;
	int pontos[TF][K] = {{30,40}, {5,25}, {10,12}, {70,70}, {50,30}, {35,45}};
	for(i=0;i<TF; i++)
		insereR(&raiz, pontos[i], 0);
	exibir(raiz, 40, 1, 20);
	return 0;
	
}

