#include<stdio.h>
#include<string.h>
#include<conio2.h>
#include "compactor.h"


int main(void)
{
	ListaTable *lt = NULL;
	Forest *f = NULL;
	char frase[200], palavra[60], cod_huff[10], flag = 0;	
	strcpy(frase, "Amo como ama o amor. Nao conheco nenhuma outra razao para amar senao amar. Que queres que te diga, alem de que te amo, se o que quero dizer-te e que te amo");
	int i=0, j=0, index=0;
	do{
		if(frase[i] == ' ')
		{
			if(i > 0)
			{
				palavra[j] = '\0';
				insertOnList(&lt, palavra);				
				j=0;								
			}
			palavra[j] = '\0';
			strcpy(palavra, " ");
			insertOnList(&lt, palavra);
			
				
		}else if(frase[i+1] == '\0')
		{		
			palavra[j] = frase[i];
			j++;
			palavra[j] = '\0';
			insertOnList(&lt, palavra);				
			j=0;	
		}
		else{
			palavra[j] = frase[i];
			j++;
		}
		i++;
	}while(i < strlen(frase));
	insereListaF(lt, &f); 
	calcFreq(&f);
	strcpy(cod_huff, "");	
	pre_ordem(f->no, cod_huff, &lt);	
	inserirArquivoB(lt);
	codificar_frase(lt, frase);
}
