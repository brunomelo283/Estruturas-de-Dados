
/* Lista Gen Conceitual */
struct reg_lista
{
 struct listagen *cabeca;
 struct listagen *cauda;
};
union info_lista
{
 char info[8];
 struct reg_lista lista;
};
struct listagen
{
 char terminal;
 union info_lista no;
};
typedef struct listagen ListaGen;



/* FILA */

struct Descritor{
	struct Fila *ini, *fim;
};
typedef struct Descritor desc;



struct Fila{
	struct Fila *prox;
	struct listagen *end;
};
typedef struct Fila Fila;


void init(desc **LD)
{
	*LD = (desc*)malloc(sizeof(desc));
	(*LD)->ini = (*LD)->fim = NULL;
}
char isEmpty(desc *LD)
{
	return LD->ini == NULL;
}

void enqueue(desc **LD, ListaGen *L)
{
	Fila *cx = (Fila*)malloc(sizeof(Fila));
	cx->prox = NULL;
	cx->end = L;
	
	
	if(isEmpty(*LD))
		(*LD)->ini = (*LD)->fim = cx;
	else
	{
		(*LD)->fim->prox = cx;
		(*LD)->fim = cx;
	}
}
void dequeue(desc **LD, ListaGen **L)
{
	Fila *aux;
	
	if((*LD)->ini == (*LD)->fim)
	{
		*L = (*LD)->ini->end;
		aux = (*LD)->ini;
		(*LD)->ini = (*LD)->fim = NULL;
		free(aux);		
	}
	else
	{
		*L = (*LD)->ini->end;
		aux = (*LD)->ini;
		(*LD)->ini = (*LD)->ini->prox;
		free(aux);
	}
}


/* FILA */


/* FILA INT */

struct DescritorN{
	struct FilaN *ini, *fim;
};
typedef struct DescritorN descN;



struct FilaN{
	struct Fila *prox;
	int n;
};
typedef struct FilaN FilaN;


void initN(descN **LD)
{
	*LD = (descN*) malloc(sizeof(descN));
	(*LD)->ini = (*LD)->fim = NULL;
}
char isEmptyN(descN *LD)
{
	return LD->ini == NULL;
}

void enqueueN(descN **LD, int n)
{
	FilaN *cx = (FilaN*)malloc(sizeof(FilaN));
	cx->prox = NULL;
	cx->n = n;
	
	
	if(isEmptyN(*LD))
		(*LD)->ini = (*LD)->fim = cx;
	else
	{
		(*LD)->fim->prox = cx;
		(*LD)->fim = cx;
	}
}
void dequeueN(descN **LD, int *n)
{
	FilaN *aux;
	
	if((*LD)->ini == (*LD)->fim)
	{
		*n = (*LD)->ini->n;
		aux = (*LD)->ini;
		(*LD)->ini = (*LD)->fim = NULL;
		free(aux);		
	}
	else
	{
		*n = (*LD)->ini->n;
		aux = (*LD)->ini;
		(*LD)->ini = (*LD)->ini->prox;
		free(aux);
	}
}


/* FILA INT */


/* PILHA */

struct pilha{
	struct listagen *end;
	struct pilha *prox;	
};
typedef struct pilha Pilha;

void initP(Pilha **p)
{
	*p = NULL;
}

void push(Pilha **p, ListaGen *end)
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



/* PILHA */

ListaGen *CriaT(char *info)
{
 ListaGen *L = (ListaGen*)malloc(sizeof(ListaGen));
 L->terminal = 1;
 strcpy(L->no.info, info);
 return L;
}

char Nula(ListaGen *L)
{
 return L==NULL;
}
char Atomo(ListaGen *L)
{
 return !Nula(L) && L->terminal;
}

ListaGen *Cons(ListaGen *H, ListaGen *T)
{
 if (Atomo(T))
 {
 printf("Cons: Segundo arqumento nao pode ser Atomo!");
 return NULL;
 }
 else
 {
 ListaGen *L = (ListaGen*)malloc(sizeof(ListaGen));
 L->terminal = 0;
 L->no.lista.cabeca = H;
 L->no.lista.cauda = T;
 return L;
 }
}


ListaGen *Head(ListaGen *L)
{
 if (Nula(L) || Atomo(L))
 {
 printf("Head: argumento deve ser lista não vazia!");
 return NULL;
 }
 else
 return L->no.lista.cabeca;
}

ListaGen *Tail(ListaGen *L)
{
 if (Nula(L) || Atomo(L))
 {
 printf("Tail: argumento deve ser lista não vazia!");
 return NULL;
 }
 else
 return L->no.lista.cauda;
}


void exibe(ListaGen *L)
{
	if(Atomo(L))
		printf("%s", L->no.info);
	
	else
	{
		printf("[");
		while(!Nula(L))
		{
			exibe(Head(L));
			L = Tail(L);
			if(!Nula(L))
				printf(",");
		}
		printf("]");
	}
}

void exibeAtomo(ListaGen *L)
{
	if(Atomo(L))
		printf("%s", L->no.info);
	else
	{
		while(!Nula(L))
		{
			exibeAtomo(Head(L));
			exibeAtomo(Tail(L));
		}
	}
}

void destroy(ListaGen **L)
{
	if(!Nula(*L))
	{
		if(Atomo(*L))			
			free(*L);					
			
				
		else
		{		
			destroy(&(*L)->no.lista.cabeca);
			destroy(&(*L)->no.lista.cauda);
			free(*L);
			*L = NULL;		
		}	
	}
	
}

ListaGen *duplicate(ListaGen *L)
{
	if(Nula(L))
		return NULL;
	if(Atomo(L))
		return CriaT(L->no.info);
	
	return Cons(duplicate(Head(L)), duplicate(Tail(L)));
	
}

char iguais(ListaGen *L, ListaGen *L2)
{
	if(Nula(L) && Nula(L2))
		return 1;
	if(Nula(L) || Nula(L2))
		return 0;
	if(Atomo(L) && Atomo(L2))
		return L->no.info == L2->no.info;			
	if(Atomo(L) || Atomo(L2))
		return 0;
	return iguais(Head(L), Head(L2)) && iguais(Tail(L), Tail(L2));
	
	
}


void ordena(ListaGen *L)
{
	ListaGen *ant;
	char strA[30];
	while(L != NULL)
	{
		if(Atomo(Head(L)))
			ant = L;
		L = Tail(L);
		if(!Nula(L) && Atomo(Head(ant)) && Atomo(Head(L)))
		{
			if(strcmp(Head(L)->no.info, Head(ant)->no.info) < 0)
			{
				strcpy(strA, ant->no.info);
				strcpy(ant->no.info, L->no.info);
				strcpy(L->no.info, strA);
			}
		}
	}
}

void BuscaElemento(ListaGen *L)
{
	ListaGen *aux;
	desc *F;
	init(&F);
	enqueue(&F, L);
	
	while(!isEmpty(F))
	{
		dequeue(&F, &L);
		ordena(L);
		aux = L;
		while(!Nula(aux))
		{
			if(!Nula(Head(aux)) && !Atomo(Head(aux)))
				enqueue(&F, Head(aux));
			aux = Tail(aux);
		}
	}
}


//void encontraL(ListaGen **L, char info[], int n)
//{
//	ListaGen *aux;
//	desc *F1, *F2;
//	descN *FN;
//	char achou = 0;
//	int niv = 1;
//	
//	if(n == 1)
//	{
//		insere(&*L, info);
//		achou = 1;
//	}
//		
//	else
//	{
//		init(&F1);
//		init(&F2);
//		initN(&FN);
//		enqueue(&F1, *L);
//		enqueueN(&FN, niv);
//		while(!isEmpty(F1) && isEmpty(F2))
//		{
//			dequeue(&F1, &aux);
//			dequeueN(&FN, &niv);
//			while(!Nula(aux))
//			{
//				if(!Nula(Head(aux)) && !Atomo(Head(aux)))
//				{
//					enqueue(&F1, Head(aux));
//					enqueueN(&FN, niv+1);
//					if(niv + 1 == n)
//						enqueue(&F2, aux);
//					
//				}
//				aux = Tail(aux);
//			}
//		}
//		while(!isEmpty(F1))
//		{
//			dequeue(&F1, &aux);
//			dequeueN(&FN, &niv);
//		}
//		while(!isEmpty(F2))
//		{
//			dequeue(&F2, &aux);
//			insere(&aux->no.lista.cabeca, info);
//			achou = 1;
//		}
//	}
//	if(!achou)
//		insereNivel(L, info, n);
//}

//void insereNivel(ListaGen **L, char info[], int n) acho q n funciona isso
//{
//	ListaGen *atual, *nova;
//	Pilha *p;
//	initP(&p);
//	int i=0;
//	atual = *L;
//	while(i < n)
//	{
//		nova = Cons(NULL, NULL);
//		if(*L == NULL)			
//			*L = atual = nova;			
//		else
//		{
//			if(i == 0)
//			{
//				while(Tail(atual) != NULL)
//					atual = Tail(atual);
//				atual->no.lista.cauda = nova;
//				atual = nova;
//			}
//			else
//			{
//				atual->no.lista.cabeca = nova;
//				atual = nova;	
//			}
//			
//		}
//		i++;				
//	}
//	if(i == n)
//	{
//		nova = CriaT(info);
//		atual->no.lista.cabeca = nova;
//	}
//}

void insere(ListaGen **L, char info[])
{
	ListaGen *ant, *atual, *aux;	
	char achou=0;
	
	if(*L == NULL)
	{		
		*L =  Cons(CriaT(info), NULL);
	}
	else
	{
		atual = *L;
		ant = *L;
		
		
		while(!Nula(atual) && !achou)
		{
			if(Atomo(Head(atual)))
			{
				if(strcmp(info, Head(atual)->no.info) > 0)
					achou = 0;
				else
				{
					if(strcmp(info, Head(atual)->no.info) != 0)
					{
						aux = Cons(CriaT(info), NULL);
						if(ant == atual)
						{						
							aux->no.lista.cauda = atual;
							*L = aux;
						}else
						{
							ant->no.lista.cauda = aux;
							aux->no.lista.cauda = atual;
						}
					
					}
					achou =1;
				}
					
			}
			if(!achou)
			{
				ant = atual;
				atual = Tail(atual);
			}
			
		}
		
		if(!achou)
		{
			aux = Cons(CriaT(info), NULL);
			ant->no.lista.cauda = aux;
		}	
	}
	
}


void excluir(ListaGen **L)
{
	ListaGen *aux, *atual;
	atual = *L;
	Pilha *P;
	initP(&P);
	push(&P, atual);
	
	while(!isEmptyP(P))
	{
		if(!Nula(atual))
			pop(&P, &atual);
		while(!Nula(atual) && !Atomo(atual))
		{
			push(&P, atual);
			atual = Head(atual);			
		}
		if(Atomo(atual))
			free(atual);
		pop(&P, &atual);
		aux = atual;
		atual = Tail(atual);
		free(aux);
		if(!Nula(atual) && Atomo(Head(atual)))
			push(&P, atual);
	}
	*L = atual;
}

void exclui_nivel(ListaGen **L,  int n)
{
	ListaGen *aux, *atual;
	desc *F1, *F2;
	descN *FN;
	int niv = 1;
	
	if(n == 1)
		excluir(&*L);
	else
	{
		init(&F1);
		init(&F2);
		initN(&FN);
		enqueue(&F1, *L);
		enqueueN(&FN, niv);
		while(!isEmpty(F1) && isEmpty(F2))
		{
			dequeue(&F1, &aux);
			dequeueN(&FN, &niv);
			while(!Nula(aux))
			{
				if(!Nula(Head(aux)) && !Atomo(Head(aux)))
				{
					enqueue(&F1, Head(aux));
					enqueueN(&FN, niv+1);
					if(niv + 1 == n)
						enqueue(&F2, aux);
					
				}
				aux = Tail(aux);
			}
		}
		while(!isEmpty(F1))
		{
			dequeue(&F1, &aux);
			dequeueN(&FN, &niv);
		}
		while(!isEmpty(F2))
		{
			dequeue(&F2, &aux);
			excluir(&aux->no.lista.cabeca);
		}
	}
}

void duplicateI(ListaGen *L, ListaGen **L2)
{
	ListaGen *atual, *nova;		
	char flag = 0;
	Pilha *p1,*p2;
	initP(&p1);
	initP(&p2);		
	push(&p1, L);
	while(!isEmptyP(p1))
	{
		if(!Nula(L))
		{
			pop(&p1, &L);
			while(!Nula(L) && !Atomo(L))
			{
				push(&p1, L);
				nova = Cons(NULL, NULL);
				if(*L2 == NULL)
					*L2 = nova;
				else
				{
					if(!flag)
						atual->no.lista.cabeca = nova;
					else
					{
						atual->no.lista.cauda = nova;
						flag = 0;
					}
				}
				push(&p2, nova);
				atual = nova;			
				L = Head(L);
			}
			if(Atomo(L))
				atual->no.lista.cabeca = CriaT(L->no.info);
			
		}				
		pop(&p1, &L);
		pop(&p2, &atual);
		L = Tail(L);
		
		if(!Nula(L))
		{
			push(&p1, L);
			flag = 1;
		}
			
		
		
	}
	

	
}

/* Lista Gen Conceitual */




