struct tree{
	int info;
	struct tree *dir, *esq;
};
typedef struct tree Tree;




Tree *CriaNo(int info)
{
	Tree *nova = (Tree*)malloc(sizeof(Tree));
	nova->info = info;
	nova->dir = nova->esq = NULL;
	return nova;
}



void calc_altura(Tree *no, int n, int *maior)
{
	if(no != NULL)
	{
		if(n > *maior)
			*maior = n;
		calc_altura(no->esq, n+1, &*maior);
		calc_altura(no->dir, n+1, &*maior);
	}
}

int altura(Tree *no){
	int maior = 0;
	calc_altura(no, 1, &maior);
	return maior;
}


void rotacao_esquerda(Tree **no)
{
	Tree *q, *temp;
	q = (*no)->dir;
	temp = q->esq;
	q->esq = *no;
	*no = q;
}

void rotacao_direita(Tree **no)
{
	Tree *q, *temp;
	q = (*no)->esq;
	temp = q->dir;
	q->dir = *no;
	*no = q;
	
}

void insertAvl(Tree **raiz, int info, int *flag)
{
	int FB, FBFilho;
	if(*raiz == NULL)
	{
		*raiz = CriaNo(info);
		*flag = 0;
	}
		
		
	else
		if(info > (*raiz)->info)
			insertAvl(&(*raiz)->dir, info, &*flag);
		else
			insertAvl(&(*raiz)->esq, info, &*flag);
		
	if(!flag)
	{
		FB = altura((*raiz)->dir) - altura((*raiz)->esq);
		*flag=1;
		if(FB == -2 || FB == 2)
		{
			
			if(FB == 2)
			{
				FBFilho = altura((*raiz)->dir->dir) - altura((*raiz)->dir->esq);
				if(FB  == -2 || FB == 2)
				{
					
					if(FB == 1)
						rotacao_esquerda(&*raiz);
					else
					{
						rotacao_direita(&(*raiz)->dir);
						rotacao_esquerda(&*raiz);
					}
				}
			}else{
				FBFilho = altura((*raiz)->esq->dir) - altura((*raiz)->esq->esq);
				if(FB == -1)
					rotacao_direita(&*raiz);
				else
				{
					rotacao_esquerda(&(*raiz)->esq);
					rotacao_direita(&*raiz);
				}
			}
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
