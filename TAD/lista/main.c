#include<stdio.h>
#include "tad.h"

int main(void)
{
	Strdin *str;
	zeraChar(&str);
	insereChar(&str, 'B');
	insereChar(&str, 'R');
	insereChar(&str, 'U');
	insereChar(&str, 'N');
	insereChar(&str, 'O');
	exibe(str);
	delAt(&str, 10, 0);
	printf("\n");
	exibe(str);
	return 0;
	
}
