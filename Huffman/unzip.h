struct table{
	int freq, symbol;
	char word[60], huffman_code[30];	
};
typedef struct table Table;



struct huffman{
	int cod;	
	struct huffman *esq, *dir;
};
typedef struct huffman Huffman;

Huffman *CriaNo(int cod)
{
	Huffman *nova = (Huffman*)malloc(sizeof(Huffman));
	nova->cod = cod;	
	nova->esq = nova->dir = NULL;	
	return nova;
}

void gerarArvore(Huffman **t)
{
	Table tabela;
	Huffman *auxH;
	int i;
	FILE *ArqB = fopen("table.dat", "rb");
	fread(&tabela, sizeof(Table),1, ArqB);
	while(!feof(ArqB))
	{
		i=0;
		auxH = *t;
		while(i < strlen(tabela.huffman_code)-1)
		{
			if(tabela.huffman_code[i] == '0')
			{
				if(auxH->esq == NULL)
					auxH->esq = CriaNo(-1);				
				auxH = auxH->esq;
			}else if(tabela.huffman_code[i] == '1'){
				if(auxH->dir == NULL)
					auxH->dir = CriaNo(-1);								
				auxH = auxH->dir;
			}
			i++;
		}
		if(tabela.huffman_code[i] == '0')
		{
			if(auxH->esq == NULL)
				auxH->esq = CriaNo(tabela.symbol);			
			
		}else if(tabela.huffman_code[i] == '1'){
			if(auxH->dir == NULL)
				auxH->dir = CriaNo(tabela.symbol);												
		}
		fread(&tabela, sizeof(Table),1, ArqB);
	}
	fclose(ArqB);
	
}


char *BuscarPalavra(int cod)
{
	FILE *ptrArq = fopen("table.dat", "rb");
	Table tabela;
	int ini = 0, meio, fim;
	fseek(ptrArq,0,2);
	fim = ftell(ptrArq)/sizeof(Table) - 1;
	meio = fim/2;
	fseek(ptrArq, sizeof(Table) * meio, 0);
	fread(&tabela,sizeof(Table), 1,ptrArq);
	while(ini < fim && cod != tabela.symbol)
	{
		if(cod < tabela.symbol)
			fim = meio -1;
		else
			ini = meio + 1;
			
		meio = (ini + fim)/2;
		fseek(ptrArq, sizeof(Table) * meio, 0);
		fread(&tabela,sizeof(Table), 1,ptrArq);
	}
	
	if(cod == tabela.symbol)
		return tabela.word;
	else
		return "";		
}

void exibir(Huffman *t, int x, int y, int dist)
{
	if(t != NULL)
	{
		gotoxy(x, y), printf("%d", t->cod);
		y++;
		if(t->esq != NULL)
			gotoxy(x- dist/2,y), printf("/");	
		exibir(t->esq, x-dist, y+1, dist/2);
		if(t->dir != NULL)
			gotoxy(x+dist/2, y), printf("\\");		
		exibir(t->dir, x+dist, y+1, dist/2);
	}
}



void unzipArqText(Huffman *h)
{
	Table table;
	Huffman *auxH = h;
	char palavra[60];
	FILE *ArqT = fopen("codificado.txt", "r");	
	char codigo[350];
	
	int i=0, j=0, cod;
	
	fgets(codigo, 350, ArqT);
	while(!feof(ArqT))
	{
		fgets(codigo, 350, ArqT);	
	}
	
	printf("Compactado: %s\n\n\n", codigo);
	printf("Descompactado: ");
	while(i < strlen(codigo))
	{
		if(codigo[i] == '0')
		{
			if(auxH->esq != NULL)
				auxH = auxH->esq;
			if(auxH->esq == NULL)
			{
				
				strcpy(palavra, BuscarPalavra(auxH->cod));
				printf("%s", palavra);
				auxH = h;
				
			}
				
		}else
		{
			if(auxH->dir != NULL)
				auxH = auxH->dir;
			if(auxH->dir == NULL)
			{
				
				strcpy(palavra, BuscarPalavra(auxH->cod));
				printf("%s", palavra);
				auxH = h;
				
			}				
		}
		i++;
	}
	
}
