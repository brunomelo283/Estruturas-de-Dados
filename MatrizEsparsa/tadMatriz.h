#define nl 5
#define nc 6
struct matrizEsparsa{
	int lin, col, valor;
	struct matrizEsparsa *pc, *pl;
};
typedef struct matrizEsparsa MatEsp;

struct lista_cruzada{
	struct matrizEsparsa *end;
	int lin, col;
	struct lista_cruzada *ant, *prox;
};
typedef lista_cruzada Lista;



/* Lista Cruzada */
void initLista(Lista **L)
{
	*L = NULL;
}

char isEmptyLista(Lista *L)
{
	return L == NULL;
}
/* Lista Cruzada */


/* Matriz Esparsa */
void initMatEsp(MatEsp **M)
{
	*M = NULL;
}

char isEmptyMat(MatEsp *M)
{
	return M == NULL;
}


void insereMatriz(Lista **L, Lista **C, int lin, int col, int valor)
{
	MatEsp *aux, *nova, *ant;
	
	
	if(lin >= 0 && lin < nl && col >= 0 && col < nc)
	{
		BuscaLinha(**L, lin);
		ocupado((*L)->end, col, &aux);
		if(aux != NULL)
			aux->valor = valor;
		else
		{
			nova = (MatEsp*)malloc(sizeof(MatEsp));
			nova->lin = lin;
			nova->col = col;
			nova->valor = valor;
			if((*L)->end == NULL)
			{
				nova->pl = NULL;
				(*L)->end = nova;
			}
			else
			{
				if(col < (*L)->end->col)
				{
					nova->pl = (*L)->end;
					(*L)->end = nova;
				}
				else
				{
					ant = (*L)->end;
					aux = ant->pl;
					while(aux != NULL && col > aux->col)
					{
						ant = aux;
						aux = aux->pl;
					}
					ant->pl = nova;
					nova->pl = aux;					
				}
			}
			BuscaColuna(**C, col);
			
			
		}
	}
}
/* Matriz Esparsa */



