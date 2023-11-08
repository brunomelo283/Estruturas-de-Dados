struct pilha{
	struct listagen *end;
	struct pilha *prox;	
};
typedef struct pilha Pilha;

void initP(Pilha **p)
{
	*p = NULL;
}

void push(Pilha **p, ListaGen end)
{
	Pilha *nova = (Pilha*)malloc(sizeof(Pilha));
	nova->end = end;
	nova->prox = *p;
	*p = nova;
}

char isEmptyP(Pilha *p)
{
	return p == NULL;
}

//int Top(Pilha *p)
//{
//	if(!isEmptyP(p))
//		return p->info;
//	return -1;
//}

void pop(Pilha **p, ListaGen **end)
{
	Pilha *aux;
	if(!isEmptyP(*p))
	{
		*end = (*p)->end;
		aux = (*p)->prox;
		free(*p);
		*p = aux;
	}
	else
		*end = NULL;
}


