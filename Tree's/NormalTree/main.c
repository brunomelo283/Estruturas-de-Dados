#include<stdio.h>
#include "tree.h"



int main(void)
{
	Tree *t = NULL, *nivel = NULL, *pai = NULL;
	int n = 1, maior=0;
	char flag=0;
	insere(&t, 8, 0, 'e');
	insere(&t, 3, 8, 'e');
	insere(&t, 1, 3, 'e');
	insere(&t, 6, 3, 'd');
	insere(&t, 4, 6, 'e');
	insere(&t, 7, 6, 'd');
	insere(&t, 10, 8, 'd');
	insere(&t, 14, 10, 'd');
	insere(&t, 13, 14, 'e');	
//	levelNodo(t, 10, &n, &nivel);
//	levelNodoI(t, 10, &n);
//	Parent(t, 13, &nivel,t, &pai);
//	printf("O pai do: %d eh: %d\n", nivel->info, pai->info);
	MaiorlevelNodo(t,&n,&maior);	
	ExibeDos(t, 40,1,maior);
	getch();

	
	return 0;
}
