struct pilha{
	int info;
	struct pilha *prox;	
};
typedef struct pilha Pilha;

void init(Pilha **p)
{
	*p = NULL;
}

void push(Pilha **p, int x)
{
	Pilha *nova = (Pilha*)malloc(sizeof(Pilha));
	nova->info = x;
	nova->prox = *p;
	*p = nova;
}

char isEmptyP(Pilha *p)
{
	return p == NULL;
}

int Top(Pilha *p)
{
	if(!isEmpty(p))
		return p->info;
	return -1;
}

void pop(Pilha **p, int *x)
{
	Pilha *aux;
	if(!isEmptyP(*p))
	{
		*x = (*p)->info;
		aux = (*p)->prox;
		free(*p);
		*p = aux;
	}
	else
		*x = -1;
}


