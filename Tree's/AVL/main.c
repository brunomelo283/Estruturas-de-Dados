#include<stdio.h>

#include "tree.h"

int main()
{
	Tree *raiz = NULL;
	int flag=1;
	insertAvl(&raiz, 6, &flag);
	insertAvl(&raiz, 2, &flag);
	insertAvl(&raiz, 8, &flag);
	insertAvl(&raiz, 10, &flag);
	insertAvl(&raiz, 9, &flag);
	insertAvl(&raiz, 12, &flag);
	exibir(raiz, 40, 1, 20);
	return 0;
}
