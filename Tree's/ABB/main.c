#include<stdio.h>
#include "tree.h"



int main(void)
{
	Tree *t=NULL, *pai=NULL, *e =NULL;
	insere(&t, 20);
	insere(&t, 10);
	insere(&t, 40);
	insere(&t, 35);
	insere(&t, 42);
	insere(&t, 15);	
	busca(t,t, 40, &e, &pai);
	exclusao(&t, e, pai);
	exibir(t, 40, 1, 20);
	return 0;
}
