/* FILA */

struct Descritor{
	struct Queue *ini, *fim;
};
typedef struct Descritor desc;



struct Queue{
	struct Queue *prox;
	Tree *end;
};
typedef struct Queue Queue;


void init(desc **LD)
{
	*LD = (desc*)malloc(sizeof(desc));
	(*LD)->ini = (*LD)->fim = NULL;
}
char isEmpty(desc *LD)
{
	return LD->ini == NULL;
}

void enqueue(desc **LD, Tree *t)
{
	Queue *cx = (Queue*)malloc(sizeof(Queue));
	cx->prox = NULL;
	cx->end = t;
	
	
	if(isEmpty(*LD))
		(*LD)->ini = (*LD)->fim = cx;
	else
	{
		(*LD)->fim->prox = cx;
		(*LD)->fim = cx;
	}
}
void dequeue(desc **LD, Tree **t)
{
	Queue *aux;
	
	if((*LD)->ini == (*LD)->fim)
	{
		*t = (*LD)->ini->end;
		aux = (*LD)->ini;
		(*LD)->ini = (*LD)->fim = NULL;
		free(aux);		
	}
	else
	{
		*t = (*LD)->ini->end;
		aux = (*LD)->ini;
		(*LD)->ini = (*LD)->ini->prox;
		free(aux);
	}
}


/* FILA */
