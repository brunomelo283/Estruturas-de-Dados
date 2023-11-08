struct tree{
	int info;
	struct tree *esq, *dir;
};
typedef struct tree Tree;


struct pilha{
	Tree *t;
	struct pilha *prox;
};
typedef struct pilha Pilha;


void init(Pilha **p)
{
	*p = NULL;	
}

char isEmpty(Pilha *p)
{
	return p == NULL;
}

void push(Pilha **p, Tree *t)
{
	Pilha *nova = (Pilha*)malloc(sizeof(Pilha));
	nova->t = t;
	nova->prox = *p;
	*p = nova;
}

void pop(Pilha **p, Tree **t)
{
	Pilha *aux;
	if(!isEmpty(*p))
	{
		*t = (*p)->t;	
		aux = (*p)->prox;
		free(*p);
		*p = aux;		
	}else{
		*t = NULL;
	}
}


Tree *CriaNo(int info)
{
	Tree *nodo = (Tree*)malloc(sizeof(Tree));
	nodo->info = info;
	nodo->esq = nodo->dir = NULL;
	return nodo;
}



void localizaNo(Tree *t, int info, Tree **pai)
{
	if(t != NULL)
	{
		if(t->info == info)
			*pai = t;
		else
		{
			localizaNo(t->esq, info, &*pai);
			if(*pai == NULL)
				localizaNo(t->dir, info, &*pai);
		}
	}
}

void insere(Tree **raiz, int info, int info_pai, char lado)
{
	Tree *pai = NULL;
	
	if(*raiz == NULL)
		*raiz = CriaNo(info);
	else
	{
		localizaNo(*raiz, info_pai, &pai);
		if(pai != NULL)
		{
			if(lado == 'e' && pai->esq == NULL)
			{
				pai->esq = CriaNo(info);
			}
			else if(lado == 'd' && pai->dir == NULL)
			{
				pai->dir = CriaNo(info);
			}
			else
			{
				printf("Nao foi possivel inserir\n");
			}
		}
		else
		{
			printf("Nodo Pai nao encontrado!\n");
		}
	}
		
}



void levelNodo(Tree *t, int info, int *n, Tree **nivel)
{	
	if(t != NULL)
	{
		if(t->info == info)
			*nivel=t;
		else
		{
			(*n)++;
			levelNodo(t->esq, info, &*n, &*nivel);
			if(*nivel == NULL)	
				levelNodo(t->dir, info, &*n, &*nivel);
			if(*nivel == NULL)			
				(*n)--;
						
				
		}
	}
}
void MaiorlevelNodo(Tree *t, int *n, int *maior)
{	
	if(t != NULL)
	{
			if(*n > *maior)
				*maior = *n;
			(*n)++;
			MaiorlevelNodo(t->esq,&*n,&*maior);
			MaiorlevelNodo(t->dir,&*n,&*maior);		
			(*n)--;
			
	}
}

void levelNodoI(Tree *t, int info, int *n)
{
	char flag=0;
	Pilha *p;
	init(&p);
	
	if(t != NULL)
		push(&p, t);
	
	while(!isEmpty(p) && !flag)
	{
		if(t != NULL)
		{
			pop(&p, &t);			
			if(t->info == info)
					flag=1;
			while(t != NULL && !flag)
			{
				if(t->info == info)
					flag=1;														
				
				if(t != NULL && !flag)
				{				
					push(&p, t);
					(*n)++;	
				}
				t= t->esq;
			}
		}
		pop(&p, &t);
		if(!flag)
		{			
			t=t->dir;		
		}
		if(!flag && t != NULL)									
			push(&p, t);
		else if(!flag)
			(*n)--;
			
	}
	while(!isEmpty(p))
	{
		pop(&p, &t);
	}
}



void Parent(Tree *t, int info, Tree **pai, Tree *aux, Tree **ant)
{
	if(t != NULL)
	{
		if(t->info == info)
		{
			*pai = t;
			*ant = aux;
		}
			
		else
		{
			Parent(t->esq, info, &*pai, t, &*ant);
			if(*pai == NULL)
				Parent(t->dir, info, &*pai, t, &*ant);
		}
	}
}


void ExibeDos(Tree *t, int x, int y, int n)
{
	
	if(t != NULL)
	{
		gotoxy(x,y);
		printf("%d", t->info);
		getch();
		y++;
		x -=  n/2;
		gotoxy(x,y);
		printf("/");		
		y++;
		x = x -  n/2;
		n--;
		ExibeDos(t->esq, x, y, n);
		y--;		
		x+=n*2;
		x++;		
		printf("\\");
		y++;
		x+=n;		
		ExibeDos(t->dir, x,y, n);	
		n++;					
		
	}
	
}
