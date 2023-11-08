#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "tadGen.h"

int main(void)
{
	ListaGen *L;
	L = NULL;
	L = Cons(CriaT("A"), Cons(Cons(CriaT("B"), NULL), NULL));
        
	exibe(L);
	//BuscaElemento(L);
//	printf("\n\n\n");
//	insereNivel(&L, "b", 2);
//	exibe(L);
	//exibe(L);

	
	return 0;
}
