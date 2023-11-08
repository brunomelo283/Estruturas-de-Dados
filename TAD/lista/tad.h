struct stringdin
{
	char letra;
	struct stringdin *prox;
}; 
typedef struct stringdin Strdin;



void zeraChar(Strdin **str)
{
	*str = NULL;
}

void insereChar(Strdin **str, char letra)
{
	 Strdin *nova, *aux;
	 nova = (Strdin*)malloc(sizeof(Strdin));
	 nova->letra = letra;
	 nova->prox = NULL;
	 
	 if(*str == NULL)
	 	*str = nova;
	else
	{
		aux = *str;
		while(aux->prox != NULL)		
			aux = aux->prox;			
		aux->prox = nova;		
	}
}


void exibe(Strdin *str)
{
	if(str != NULL)
	{
		printf("%c", str->letra);
		exibe(str->prox);
	}
}
void delAt(Strdin **str, int nro, int start)
{
	int i;
	Strdin *aux = *str, *ant = *str;
	for(i = 0; aux != NULL && i < start; i++)
	{
		ant = aux;
		aux = aux->prox;
	}
	
	for(i=0;aux != NULL && i < nro; i++)
	{
		if(aux != ant)
		{
			ant->prox = aux -> prox;
			free(aux);
			aux = ant->prox;
		}else{
			*str = (*str)->prox;
			free(aux);
			aux = ant = *str;
		}
	
	}
}
