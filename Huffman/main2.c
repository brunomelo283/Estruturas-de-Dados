#include<stdio.h>
#include<string.h>
#include<conio2.h>
#include "unzip.h"



int main(void)
{
	Huffman *h;
	h = CriaNo(-1);
	gerarArvore(&h);
	//exibir(h, 40, 1, 20);
	unzipArqText(h);
	return 0;
}
