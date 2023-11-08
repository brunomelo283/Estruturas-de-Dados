#include<stdio.h>
#include<stdlib.h>
#include "tadpilha.h"

int main()
{
	Pilha *p;
	int value;
	init(&p);
	push(&p, 10);
	push(&p, 11);
	push(&p, 12);
	push(&p, 13);
//	value = Top(p);	
	pop(&p, &value);
	printf("%d\n", value);
	pop(&p, &value);
	printf("%d\n", value);
	pop(&p, &value);
	printf("%d\n", value);
	pop(&p, &value);
	printf("%d\n", value);
	pop(&p, &value);
	printf("%d\n", value);
	
	return 0;
	
}
