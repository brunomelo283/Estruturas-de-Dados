struct table{
	int freq, symbol;
	char word[60], huffman_code[30];	
};
typedef struct table Table;

struct huffman{
	int cod, freq;
	struct huffman *esq, *dir;
};
typedef struct huffman Huffman;


struct forest{
	struct forest *prox;
	Huffman *no;
};
typedef struct forest Forest;

struct listaTable{
	Table table;
	struct listaTable *prox;
};
typedef struct listaTable ListaTable;


ListaTable *criaCxTable(Table tabela)
{
	ListaTable *nova = (ListaTable*)malloc(sizeof(ListaTable));
	nova->table = tabela;
	nova->prox = NULL;
	return nova;
}

void insertOnList(ListaTable **lt, char word[60])
{
	int cod = 1;	
	Table table;
	table.freq = 1;
	strcpy(table.word, word);
	
	if(*lt == NULL)
	{
		table.symbol = cod;
		*lt = criaCxTable(table);
	}
		
	else
	{
		ListaTable *aux = *lt;
		cod = 2;		
		while(aux->prox != NULL && strcmp(aux->table.word, word) != 0) 
		{
			cod++;	
			aux = aux->prox;
		}
			
		
		if(strcmp(aux->table.word, word) == 0)
		{
			aux->table.freq++;
		}
		else
		{
			table.symbol = cod;
			aux->prox = criaCxTable(table);
		}
	}
}



Huffman *CriaNo(int cod, int freq)
{
	Huffman *no = (Huffman*)malloc(sizeof(Huffman));
	no->cod = cod;
	no->freq = freq;
	no->esq = no->dir = NULL;	
	return no;
}

void insertForest(Forest **f, int cod, int freq, Huffman *no)
{
	Forest *ant, *aux; 
	Forest *nova = (Forest*)malloc(sizeof(Forest));
	nova->no = no;
	nova->prox = NULL;

	if(*f == NULL)
	{
		*f = nova;	
	}else
	{
		ant = aux = *f;
		while(aux->prox != NULL && freq > aux->no->freq)	
		{
			ant = aux;
			aux = aux->prox;
		}
		if(freq < aux->no->freq)
		{
			if(aux == ant)
			{
				nova->prox = aux;
				*f = nova;	
			}else
			{
				ant->prox = nova;
				nova->prox = aux;				
			}
		}else{
			if(freq > aux->no->freq)
			{
				aux->prox = nova;
			}else{
				if(aux-> prox == NULL)
				{
					aux->prox = nova;
				}
				else
				{
					if(aux == ant)
					{
						nova->prox = aux->prox;
						aux->prox = nova;
						
					}
					else
					{
						ant->prox = nova;
						nova->prox = aux;
					}
					
				}
			}
		}
	}
}


void insereListaF(ListaTable *lt, Forest **f)
{
	Huffman *no;
	while(lt != NULL)
	{
		
		no = CriaNo(lt->table.symbol, lt->table.freq);
		insertForest(&*f, lt->table.symbol, lt->table.freq, no);
		lt = lt->prox;
	}
	
}

void exibe_tabela(ListaTable *lt)
{		
	while(lt != NULL)
	{
		printf("[ %d, %s, %d, %s]  ", lt->table.symbol, lt->table.word, lt->table.freq, lt->table.huffman_code);				
		lt = lt->prox;
	}
	printf("\n");
}
void calcFreq(Forest **f)
{	
	int novaFreq;
	Huffman *auxNo;
	Forest *aux, *p, *novaList;
	novaList = (Forest*)malloc(sizeof(Forest));
	novaList->prox = NULL;
	aux = *f;	
	p = aux->prox;
	while(aux->prox != NULL)
	{
		novaFreq = aux->no->freq + p->no->freq;
		auxNo = CriaNo(-1, novaFreq);
		auxNo->esq = aux->no;
		auxNo->dir = p->no;
		insertForest(&*f, -1, novaFreq, auxNo);
		*f = p->prox;
		free(aux);
		free(p);
		aux = *f;
		p = aux->prox;
	}
}

void exibeForest(Forest *f)
{
	printf("\n\n");
	while(f != NULL)
	{
		printf("[%d, %d] ", f->no->cod, f->no->freq);
		f = f->prox;
	}
	printf("\n\n");
}



void inserirTabela(ListaTable **lt, int cod, char huff_code[])
{
	ListaTable *aux;
	aux = *lt;
	while(aux != NULL && aux->table.symbol != cod)
		aux = aux->prox;
		
	if(aux->table.symbol == cod)
		strcpy(aux->table.huffman_code, huff_code);
}


void inserirArquivoB(ListaTable *lt)
{
	FILE *ArqB = fopen("table.dat", "wb");
	while(lt != NULL)
	{
		fwrite(&lt->table, sizeof(lt->table), 1, ArqB);
		lt = lt->prox;
	}
	fclose(ArqB);
}
void pre_ordem(Huffman *tree,char codigo[], ListaTable **tabela)
{
	if(tree != NULL)
	{
		if(tree->esq == NULL && tree->dir == NULL)
		{
			inserirTabela(&*tabela, tree->cod, codigo);						
			codigo[strlen(codigo)-1] = '\0';						
		}
		else
		{
			pre_ordem(tree->esq, strcat(codigo, "0"), &*tabela);
			pre_ordem(tree->dir, strcat(codigo, "1"), &*tabela);
			codigo[strlen(codigo)-1] = '\0';
		}
		
	}
}

ListaTable *searchOnListT(ListaTable *lt, char word[])
{
	while(lt != NULL && strcmp(word, lt->table.word) != 0)
		lt = lt->prox;
	
	return lt;
}

void codificar_frase(ListaTable *lt, char frase[])
{
	int i = 0;
	int j = 0;
	char palavra[60], codificado[350];
	FILE *ArqT = fopen("codificado.txt", "w");
	strcpy(codificado, "");
	ListaTable *auxT;		
	do{
		if(frase[i] == ' ')
		{
			if(i > 0)
			{
				palavra[j] = '\0';
				auxT = searchOnListT(lt, palavra);
				strcat(codificado, auxT->table.huffman_code);			
				j=0;								
			}
			palavra[j] = '\0';
			strcpy(palavra, " ");
			auxT = searchOnListT(lt, palavra);
			strcat(codificado, auxT->table.huffman_code);								
		}else if(frase[i+1] == '\0')
		{		
			palavra[j] = frase[i];
			j++;
			palavra[j] = '\0';
			auxT = searchOnListT(lt, palavra);
			strcat(codificado, auxT->table.huffman_code);			
			j=0;	
		}
		else{
			palavra[j] = frase[i];
			j++;
		}
		i++;
	}while(i < strlen(frase));
	printf("Frase codificada com sucesso\n");
	printf("Codigo Gerado: %s\n", codificado);
	fputs(codificado, ArqT);
	fclose(ArqT);
}




