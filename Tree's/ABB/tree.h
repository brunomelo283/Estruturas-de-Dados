struct tree{
	int info;
	struct tree *esq, *dir;
};
typedef struct tree Tree;


Tree *CriaNo(int n)
{
	Tree *no = (Tree*)malloc(sizeof(Tree));
	no->info = n;
	no->esq = no->dir = NULL;
	return no;
}

void insere(Tree **t, int n)
{
	if(*t == NULL)
		*t = CriaNo(n);
	else
	{
		if(n > (*t)->info)
			insere(&(*t)->dir, n);
		else if(n < (*t)->info)
			insere(&(*t)->esq, n);					
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
void busca(Tree *t, Tree *ant, int info, Tree **e, Tree **pai)
{
	if(t != NULL)
	{
		
		if(t->info == info)
		{
			*pai = ant;
			*e = t;			
		}
			
			
		else
		{
			if(info > t->info)
				busca(t->dir, t,info, &*e, &*pai);
			else
				busca(t->esq, t,info, &*e, &*pai);
		}
	}
}

void exibir(Tree *t, int x, int y, int dist)
{
	if(t != NULL)
	{
		gotoxy(x, y), printf("%d", t->info);
		y++;
		if(t->esq != NULL)
			gotoxy(x- dist/2,y), printf("/");	
		exibir(t->esq, x-dist, y+1, dist/2);
		if(t->dir != NULL)
			gotoxy(x+dist/2, y), printf("\\");		
		exibir(t->dir, x+dist, y+1, dist/2);
	}
}

void  exclusao(Tree **t, Tree *e, Tree *pai)
{
	Tree *sub, *paisub;
	int aux;
	
	if(e->dir == NULL && e->esq == NULL)//é folha
	{
		if(e != pai)
		{
			if(e->info > pai->info)
				e->dir = NULL;
			else
				e->esq = NULL;
		}
		else
			*t = NULL;
		free(e);
	}else{
		if(e->dir == NULL || e->esq == NULL)//tem um filho
		{
			if(e != pai)
			{
				if(e->info > pai->info)
				{
					if(e->dir != NULL)
						pai->dir = e->dir;
					else if(e->esq != NULL)
						pai->dir = e->esq;
				}else{
					if(e->dir != NULL)
						pai->esq = e->dir;
					else
						pai->esq = e->esq;
				}
				free(e);
			}else{
				if(e->dir != NULL)
					*t = e->dir;
				else if(e->esq != NULL)
					*t = e->esq;
				free(e);
			}
			
		}else{// tem 2 filho
			paisub = e;
			sub = e->dir;
			while(sub->esq != NULL)
			{
				paisub = sub;
				sub = sub->esq;
			}
			aux = sub->info;
			exclusao(&*t, sub, paisub);
			e->info = aux;
		}
	}
	
}


