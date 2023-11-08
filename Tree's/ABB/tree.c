struct tree{
	int info;
	struct tree *esq, *dir;
};
typedef struct tree Tree;



void insere(Tree **t, int n)
{
	if(*t == NULL)
		(*t)->info = n;
	else
	{
		if(info > (*t)->info)
			insere((*t)->dir, n);
		else if(info < (*t)->info)
			insere((*t)->esq, n);					
	}
}


void pre_ordem(Tree *t)
{
	if(t != NULL)
	{
		printf("%d ", t->info);
		pre_ordem(t->esq);
		pre_ordem(t->dir);
	}
}


