/* Lista de String Auxiliar */

struct tpString{
	char str[50];
	int length;
	char paragrafo;
	char linha;
	struct tpString *prox;
}; 
typedef struct tpString string;



void initString(string **lstring)
{
	*lstring = NULL;
}


void insereString(string **lstring, char str[50], int length, char paragrafo, char linha)
{
	string *cx = (string*)malloc(sizeof(string));
	string *aux;
	cx->length = length;
	cx->paragrafo = paragrafo;
	cx->linha = linha;
	cx->prox = NULL;
	strcpy(cx->str, str);
	
	if(*lstring == NULL)
	{
		*lstring = cx;
	}
	else
	{
		aux = *lstring;
		
		while(aux->prox != NULL)
			aux = aux->prox;
		
		aux->prox = cx;		
	}
}

/* Lista GEN DE PALAVRAS */

struct palavras
{
	char letra;
	char final;
	struct palavras *prim, *prox;	
};
typedef struct palavras ListaGen;



ListaGen *CriaNo(char letra, int i, int len)
{
	ListaGen *nova = (ListaGen*)malloc(sizeof(ListaGen));
	nova->letra = letra;
	if(i == len-1)
		nova->final = 'T';
	else
		nova->final = 'F';
	nova->prim = NULL;
	nova->prox = NULL;
	
	return nova;
}

void insereLetras(ListaGen **laux, char palavra[], int i)
{
	ListaGen *nova, *aux;
	if(*laux == NULL)
	{
		nova = CriaNo(palavra[i], i, strlen(palavra));
		*laux = nova;
	}	
	aux = *laux;	
	for(i++; i < strlen(palavra); i++)
	{
		nova = CriaNo(palavra[i], i, strlen(palavra));
		aux->prim = nova;
		aux = nova;
	}					
}
char buscaPalavra(ListaGen *L, char letras[], char palavra[])
{
	ListaGen *atual,*aux2, *aux;
	char recomendar=0, final=1;
	int i=0,j=0;
		aux = L;
		for(i=0; i<strlen(letras); i++)
		{
			recomendar=0;
			final=1;		
			while(aux != NULL && aux->letra != letras[i])
			{
				aux = aux->prox;			
			}
				
			

			aux2 = aux;	
			if(aux2 != NULL && aux2->letra == letras[i])
			{
				
				while(aux2 != NULL && final)
				{
					if(aux2->final == 'T')
					{
						palavra[j] = aux2->letra;
						j++;
						palavra[j] = '\0';
						final=0;
						recomendar=1;
					}
					else
					{					
						palavra[j] = aux2->letra;
						j++;
						aux2 = aux2->prim;	
					}
					
				}
				
			}
			if(aux != NULL)			
				aux = aux->prim;
			else
				palavra[0] = '\0';
			j=i+1;					
		}
		
	
	
	
	return recomendar;
}
void busca(ListaGen *atual, char letra, ListaGen **ant, ListaGen **aux)
{
	*ant = *aux = atual;
	while(*aux != NULL && (*aux)->letra < letra)
	{
		*ant = *aux;				
		*aux = (*aux)->prox;
	}				
}
void inserePalavra(ListaGen **lpalavras, char palavra[])
{
	ListaGen *pai, *atual, *ant, *aux, *nova;
	int i;
	char flag =1;
	
	if(*lpalavras == NULL)
		insereLetras(&*lpalavras, palavra, 0);
	else
	{
		pai = atual = *lpalavras;
		for(i = 0; i < strlen(palavra) && flag; i++)
		{
			busca(atual, palavra[i], &ant, &aux);
			if(aux != NULL && aux -> letra == palavra[i])
			{
				pai = aux;
				atual = pai->prim;
				if(atual == NULL)
				{
					insereLetras(&pai->prim, palavra, i+1);
					flag =0;
				}
				
			}
			else
			{
				nova = CriaNo(palavra[i], i, strlen(palavra));
				if(ant == aux)
				{
					if(*lpalavras == aux)
					{
						nova->prox = *lpalavras;
						*lpalavras = nova;
					}
					else
					{
						nova->prox = aux;
						pai->prim = nova;
					}
				}
				else
				{
					ant->prox = nova;
					nova->prox = aux;
				}
				insereLetras(&nova->prim, palavra, i+1);
				flag =0;
			}
			
		}
		if(flag)
			aux->final = 'T';
	}
}
/* Lista GEN DE PALAVRAS */

/* Lista de String Auxiliar */
struct tpLinhas{
	int nro;	
	struct tpLinhas *top, *bottom;
	struct tpColunas *inicioL;
};
typedef struct tpLinhas linha;

struct tpColunas{
	char letra;
	struct tpColunas *prox, *ant;
};
typedef struct tpColunas coluna;

/* LINHAS */

void destroyCol(coluna **col)
{
	if(*col != NULL)
	{
		destroyCol(&(*col)->prox);
		free(*col);
		*col = NULL;
	}	
}
void destroyStruct(linha **ini)
{
	linha *aux;
	while(*ini != NULL)
	{
		destroyCol(&(*ini)->inicioL);
		aux = *ini;
		*ini = (*ini)->bottom;
		free(aux);
	}
}
void initLinha(linha **lin){
	*lin = NULL;
}

char isEmptyL(linha *lin)
{
	return lin == NULL;
}

void criaLinha(linha **inicio, linha **lin, coluna **cursor)
{
	//Cria caixa
	int x, y;
	coluna *aux;
	coluna *col = (coluna*)malloc(sizeof(coluna));	
	linha *cx = (linha*)malloc(sizeof(linha));
	cx->top = NULL;
	cx->bottom = NULL;
	cx->nro = 0;
	cx->inicioL = col;
	cx->inicioL->prox = NULL;	
	cx->inicioL->ant = NULL;
	cx->inicioL->letra = NULL;
	
	
	
	if(isEmptyL(*inicio))
	{
		*lin = *inicio = cx;
		*cursor = cx->inicioL;		
	}
		
	else
	{
		if(*lin == *inicio && (*cursor)->ant == NULL)
		{
			
			cx->bottom = (*inicio);	
			(*inicio)->top = cx;
			(*inicio) = cx;						
		}
		else
		{
			if((*cursor)->prox == NULL)
			{
				if((*lin)->bottom == NULL)
				{
					cx->top = *lin;
					(*lin)->bottom = cx;
					*lin = cx;	
					*cursor = cx->inicioL;		
				}
				else
				{
					cx->top = *lin;
					cx->bottom = (*lin)->bottom;
					(*lin)->bottom->top = cx;
					(*lin)->bottom = cx;
					*lin = cx;
					*cursor = cx->inicioL;		
				}	
			}
			else if((*cursor)->ant == NULL)
			{
				cx->top = (*lin)->top;
				cx->bottom = *lin;
				(*lin)->top->bottom = cx;
				(*lin)->top = cx;				
			}else
			{
				aux = *cursor;
				while(aux->prox != NULL)				
				{
					aux=aux->prox;
					(*lin)->nro--;
				}
					
				cx->top = *lin;
				cx->bottom = NULL;					
				col->prox = NULL;
				col->ant = (*cursor)->ant;
				col->letra = NULL;
				(*cursor)->ant->prox = col;					
				(*cursor)->ant = NULL;   
				cx->inicioL = *cursor;
				*cursor = cx->inicioL;
				if((*lin)->bottom == NULL)
				{
					(*lin)->bottom = cx;					
					*lin = cx;		
				}
				else
				{
					cx->bottom = (*lin)->bottom;				
 					(*lin)->bottom->top = cx;
					(*lin)->bottom = cx;					
					*lin = cx;	
				}
							
			}
			
		}							
	}
	x = wherex(); 
	y = wherey();
	gotoxy(18, 22);
	printf("%02d", y-2);		
	gotoxy(x, y);
	
	
	


	
				
}
/* LINHAS */





/* COLUNAS */
void initColuna(coluna **col)
{
	*col = NULL;
}

char isEmptyC(coluna *col)
{
	return col == NULL;
}

void criaColuna(coluna **cursor, linha **lin, linha **ini, linha **page, char letra, int flagInsert)
{
	int x, y;
	coluna *aux;
	coluna *cx = (coluna*)malloc(sizeof(coluna));	
	cx->ant = NULL;
	cx->prox = NULL;
	cx->letra = NULL;
	if(flagInsert == 0)				
	{
		if((*cursor)->prox == NULL)		
		{
			if((*lin)->nro < 79)
			{
				(*cursor)->letra = letra;
				//CRIA O SENTINELA APOS INSERIR UMA LETRA			
				cx->ant = cursor;
				(*cursor)->prox = cx;
				cx->ant = *cursor;
				(*cursor) = cx;		
				(*lin)->nro++;			
			}else{
				criaLinha(&*ini, &*lin, &*cursor);
				criaColuna(&*cursor, &*lin, &*ini, &*page, letra, flagInsert);			
				ajustarTela(*ini, *cursor, &*page,1, wherey(), flagInsert);
				printf("%c", letra);
			}
			
		}else{
			if((*cursor)->ant == NULL)
			{
				if((*lin)->nro < 79)
				{
					cx->prox = *cursor;
					(*cursor)->ant = cx;			
					(*lin)->inicioL = cx;
					(*cursor)->ant->letra = letra;					
				}else{	
					cx->prox = *cursor;
					(*cursor)->ant = cx;			
					(*lin)->inicioL = cx;
					(*cursor)->ant->letra = letra;
					while((*cursor)->prox->prox != NULL)
						 *cursor = (*cursor)->prox;
			
																
					criaLinha(&*ini, &*lin, &*cursor);
					*cursor = (*cursor)->prox;
					printf("\n");
					
					ajustarTela(*ini, *cursor, &*page,wherex()+1, wherey(), flagInsert);
					
				}
				(*lin)->nro++;				
			}else {
				if((*lin)->nro < 79)
				{
					cx->prox = *cursor;
					cx->ant = (*cursor)->ant;
					(*cursor)->ant->prox = cx;
					(*cursor)->ant = cx;				
					(*cursor)->ant->letra = letra;								
				}else{
					cx->prox = *cursor;
					cx->ant = (*cursor)->ant;
					(*cursor)->ant->prox = cx;
					(*cursor)->ant = cx;				
					(*cursor)->ant->letra = letra;
					(*lin)->nro++;								
					while((*cursor)->prox->prox != NULL)
						 *cursor = (*cursor)->prox;
					criaLinha(&*ini, &*lin, &*cursor);
					*cursor = (*cursor)->prox;
					
					printf("\n");
					
					ajustarTela(*ini, *cursor, &*page,wherex()+1, wherey(), flagInsert);
				}
				(*lin)->nro++;
			}		
				//(*cursor)->letra = letra;
		}
	}else{
		if((*cursor)->prox != NULL)
		{			
			(*cursor)->letra = letra;
			*cursor = (*cursor)->prox;
			(*lin)->nro++;
		}else{
			(*cursor)->letra = letra;
			cx->ant = *cursor;	
			(*cursor)->prox = cx;
			*cursor = cx;
			(*lin)->nro++;
		}
	}
	
	
	if((*cursor)->ant != NULL)
	{
		x = wherex();
		y = wherey();
		gotoxy(8, 22);
		printf("%02d", x);
		gotoxy(x, y);
	}	

}
/* COLUNAS */


/* Salvar arquivo */

void saveFile(FILE *ptrArq, char nomearq[50],linha *ini)
{
	ptrArq = fopen(nomearq, "w");
	linha *aux;
	coluna *auxCursor;
	aux = ini;
	while(aux != NULL)
	{
		auxCursor = aux->inicioL;
		while(auxCursor->prox != NULL)
		{			
			fputc(auxCursor->letra, ptrArq);

			auxCursor = auxCursor->prox;
		}
		if(aux->bottom != NULL)
			fputc('\n', ptrArq);
		aux = aux->bottom;
	}
	fclose(ptrArq);
}

/* Salvar arquivo */


/* Abrir arquivo */

void openFile(FILE *ptrArq, char nomearq[50], linha **ini, linha **lin, coluna **col, linha **page)
{
	char car;
	ptrArq = fopen(nomearq, "r");
	if(ptrArq == NULL)
		printf("Arquivo nao encontrado\n");
	else
	{
		car = fgetc(ptrArq);
		while(!feof(ptrArq))
		{			
			if(car == '\n')	
				criaLinha(&*ini, &*lin, &*col);	
							
				
			
				
			else
				criaColuna(&*col, &*lin, &*ini, &*page, car, 0);
			car = fgetc(ptrArq);	
		}	
	}
	fclose(ptrArq);
}
/* Abrir arquivo */


/* Exibir Texto */

void exibirTexto(linha *ini)
{
	int flagNegrito = 0;
	linha *aux;
	coluna *auxCursor;
    int cont=0;
	
	aux = ini;
	while(aux != NULL && cont <= 16)
	{		
		auxCursor = aux->inicioL;
		while(auxCursor->prox != NULL)
		{
			if(auxCursor->letra == 'з' && flagNegrito == 0)
			{
				flagNegrito = 1;
			}				
			else if(auxCursor->letra == 'з' && flagNegrito == 1)
			{
				flagNegrito = 0;	
			}				
			else
			{
				if(flagNegrito == 1)
				{
					textcolor(1);
				}else
				{
					textcolor(15);
				}			
				printf("%c", auxCursor->letra);				
			}
			auxCursor = auxCursor->prox;	
			
		}
		if(aux->bottom != NULL)
			printf("\n");
		aux = aux->bottom;	
		cont++;		
	}
}

/* Exibir Texto */


/* Mover Cursor ou Linha */

void moveCursorLinha(int tipo, linha **lin, linha **page, coluna **cursor)
{
	int i,x,y, contx=1;
	coluna *auxF, *auxI;
	auxF = *cursor;	
	auxI = (*lin)->inicioL;
	if(tipo == 72)
	{
		if((*lin)->top != NULL)
		{
			x = wherex();
			y = wherey()-1;
			*lin = (*lin)->top;
			gotoxy(18, 22);
			printf("%02d", y-3);									
			*cursor = (*lin)->inicioL;			
			while((*cursor)->prox != NULL && auxF != auxI)
			{
				*cursor = (*cursor)->prox;
				auxI = auxI->prox;
				contx++;
			}
			gotoxy(8, 22);
			printf("%02d", contx);
			if(y==3)
			{
				if((*page)->top != NULL)
					*page = (*page)->top;
				y=y+1;				
			}
			gotoxy(contx, y);
		}	
	}
	else if(tipo == 77)
	{
		if((*cursor)->prox != NULL)
		{
			x = wherex()+1;
			y = wherey();
			*cursor = (*cursor)->prox;
			gotoxy(8, 22);
			printf("%02d", x);
			gotoxy(x, y);	
		}
			
	}
	else if(tipo == 80)
	{
	
		coluna *auxF, *auxI;
		auxF = *cursor;	
		auxI = (*lin)->inicioL;
		if((*lin)->bottom != NULL)
		{
			x = wherex();
			y = wherey() + 1;
			*lin = (*lin)->bottom;
			gotoxy(18, 22);
			printf("%02d", y-3);
			
			*cursor = (*lin)->inicioL;
			while((*cursor)->prox != NULL && auxI != NULL && auxF != NULL && auxF != auxI)
			{
				*cursor = (*cursor)->prox;
				auxI = auxI->prox;
				contx++;
			}
			gotoxy(8, 22);
			printf("%02d", contx);
			if(y==21)
			{
				if((*page)->top != NULL)
					*page = (*page)->top;
				y=y-1;				
			}
			gotoxy(contx, y);
			
		}	
	}
	else if(tipo == 75)
	{
		x = wherex()-1;
		y = wherey();
		if((*cursor)->ant != NULL && x > 0)
		{
			
			*cursor = (*cursor)->ant;
			gotoxy(wherex()-1, wherey());
			gotoxy(8, 22);
			printf("%02d", x);
			gotoxy(x, y);	
		}
		
	}else if(tipo == 71)
	{
		x = wherex();
		y = wherey();
		while((*cursor)->ant != NULL)
		{
			*cursor = (*cursor)->ant;
			x--;
		}
		gotoxy(8, 22);
		printf("%02d", x);
		gotoxy(x, y);
		
	}else if(tipo == 79)
	{
		x = wherex();
		y = wherey();
		while((*cursor)->prox != NULL)
		{
			*cursor = (*cursor)->prox;
			x++;
		}
		gotoxy(8, 22);
		printf("%02d", x);
		gotoxy(x, y);
		
	}else if(tipo == 73){
		x = wherex();
		y = wherey();
		while((*lin) != NULL && *lin  != *page && y != 3)
		{
			*lin = (*lin)->top;
			*cursor = (*lin)->inicioL;
			y--;
		}
		gotoxy(18, 22);
		printf("%02d", y);
		gotoxy(x, y);
	}else if(tipo == 81){
		x = wherex();
		y = wherey();
		while((*lin)->bottom != NULL &&  y != 20)
		{
			*lin = (*lin)->bottom;
			*cursor = (*lin)->inicioL;
			y++;
		}
		
		
		gotoxy(18, 22);
		printf("%02d", y);
		gotoxy(x, y);
	}
}

/* Mover Cursor ou Linha */



/* Apagar um caracter da lista */

void deleteChar(int op, linha **lin, coluna **cursor, linha *ini, linha **page, int flagInsert)
{
	int x, y,  contx=1;
	linha  *auxLinha;
	coluna *auxCursor, *prim;
	if(op == 8)
	{
										
		if((*cursor)->ant == NULL)
		{
			if((*lin)->top != NULL)
			{	
							
				prim = auxCursor = *cursor;
				*cursor = (*lin)->top->inicioL;
				while((*cursor)->prox != NULL)	
				{
					*cursor = (*cursor)->prox;	
					contx++;
				}								
				while(auxCursor->prox != NULL)
				{
					if((*lin)->top->nro < 79)
					{
						if((*cursor)->ant == NULL)
						{
							(*lin)->inicioL = auxCursor->prox;
							auxCursor->prox->ant = NULL;
							auxCursor->prox = *cursor;
							(*cursor)->ant = auxCursor;
							(*lin)->top->inicioL = auxCursor;
							auxCursor = (*lin)->inicioL;
							
						}
						else{
							(*lin)->inicioL = auxCursor->prox;
							auxCursor->ant = (*cursor)->ant;
							(*cursor)->ant->prox = 	auxCursor;						
							(*cursor)->ant = auxCursor;
							auxCursor->prox = *cursor;
							(*lin)->top->nro++;	
							 auxCursor = (*lin)->inicioL;
						}
					
					}else{
						auxCursor = auxCursor->prox;	
					}
				}
				if(prim->prox != NULL && (*lin)->top->nro < 79)
					*cursor = prim;
				if(auxCursor->ant == NULL)
				{
					free(auxCursor);
					if((*lin)->bottom == NULL)
					{				
						auxLinha = *lin;
						(*lin)->top->bottom = NULL;
						*lin = (*lin)->top;
						free(auxLinha);				
					}else
					{						
						auxLinha = *lin;
						(*lin)->top->bottom = (*lin)->bottom;
						(*lin)->bottom->top = (*lin)->top;
						*lin =  (*lin)->top;
						free(auxLinha);
					}	
				}else
				{
					*lin =  (*lin)->top;
				}
				y = wherey();
				ajustarTela(ini,*cursor, &*page, contx,y-1, flagInsert);	
				x = wherex();
				y = wherey();		
				gotoxy(x,y);
			}			
		}else{			
			auxCursor = (*cursor)->ant;			
			if(auxCursor != NULL)
			{	
				if(auxCursor->ant == NULL)
				{
					(*cursor)->ant = NULL;
					(*lin)->inicioL = (*cursor);				
					free(auxCursor);
					
				
				}else{				
					auxCursor->ant->prox =  auxCursor->prox;
					auxCursor->prox->ant = auxCursor->ant;
					free(auxCursor);
				}
			}
			x = wherex();
			y = wherey();
			ajustarTela(ini,*cursor, &*page, x-1,y, flagInsert);
			(*lin)->nro--;
		}
	}else{
		if((*lin)->bottom != NULL)
		{						
			if((*cursor)->prox == NULL)
			{
				
				if((*lin)->nro < 79)
				{
					auxCursor = *cursor;
					*cursor = (*lin)->bottom->inicioL;
					prim = *cursor;
					while((*cursor)->prox != NULL)
					{
						if((*lin)->nro < 79)
						{
							(*lin)->bottom->inicioL = (*cursor)->prox;
							(*cursor)->prox->ant = NULL;
							(*cursor)->prox = auxCursor;
							(*cursor)->ant = auxCursor->ant;
							auxCursor->ant->prox = *cursor;
							auxCursor->ant = *cursor;
							*cursor = (*lin)->bottom->inicioL;
							(*lin)->nro++;						
						}else{
							*cursor = (*cursor)->prox;
						}
					}
				
					if(prim->prox != NULL)
						*cursor = prim;
					auxLinha = (*lin)->bottom;
					
					if(auxLinha->inicioL->prox == NULL)
					{
						if(auxLinha->bottom == NULL)
						{
							(*lin)->bottom = NULL;
							free(auxLinha);
						}else{
							(*lin)->bottom = auxLinha->bottom;
							auxLinha->bottom->top = (*lin);
							free(auxLinha);
						}
					}
				}
			
				
			}else{
				if((*cursor)->ant == NULL)
				{
					(*cursor)->prox->ant = NULL;
					(*lin)->inicioL = (*cursor)->prox;
					free(*cursor);
					*cursor = (*lin)->inicioL;
					(*lin)->nro--;
				}else{
					(*cursor)->ant->prox = (*cursor)->prox;
					(*cursor)->prox->ant = (*cursor)->ant;
					auxCursor = *cursor;
					*cursor = (*cursor)->prox;
					free(auxCursor);		
					(*lin)->nro--;
				}
			}
		}else{
			if((*cursor)->prox != NULL)
			{
				if((*cursor)->ant == NULL)
				{
					(*cursor)->prox->ant = NULL;
					(*lin)->inicioL = (*cursor)->prox;
					free(*cursor);
					*cursor = (*lin)->inicioL;					
				}else{
					(*cursor)->ant->prox = (*cursor)->prox;
					(*cursor)->prox->ant = (*cursor)->ant;
					auxCursor = *cursor;
					*cursor = (*cursor)->prox;
					free(auxCursor);		
				}
				
			}
			
		}
		
	}
	
}


/* Apagar um caracter da lista */




/* Ajustar Tela ao fazer uma aчуo */

void ajustarTela(linha *ini,coluna *cursor, linha **page, int x, int y, int flagInsert)
{
	int i=0,j,cont=0;
	
	
	linha *aux;
	coluna *auxCursor;

	
	textbackground(0);
	for(i=0; i < 80; i++)
	{
		for(j=4; j< 21; j++)
		{
			gotoxy(i, j);
			printf("%c", NULL);
		}
	}
			
	gotoxy(1,4);
	aux = *page;
	
	if(y== 20)
	{
		if((*page)->bottom != NULL)
			*page = (*page)->bottom;
		y=19;						
	}	
			
	
	exibirTexto(*page);

	
	gotoxy(x, y);
	if(flagInsert == 1)
	{
		textbackground(8);
		printf("%c", cursor->letra);
	}
	gotoxy(x, y);		
}

/* Ajustar Tela ao fazer uma aчуo */

/* Limpa Tela*/
void limpaTela()
{
	int i,j;
	textbackground(0);
	for(i=0; i < 80; i++)
	{
		for(j=4; j< 21; j++)
		{
			gotoxy(i, j);
			printf("%c", NULL);
		}
	}
}
void limpaTela2()
{
	int i,j;
	textbackground(0);
	for(i=0; i < 80; i++)
	{
		for(j=0; j< 25; j++)
		{
			gotoxy(i, j);
			printf("%c", NULL);
		}
	}
}
/* Limpa Tela */

/*  EXIBIR AO PRESSIONAR F5 */

void JustifyText(linha *ini, int pl, int re, int rd){
	string *lstr, *aux, *atual, *pagina, *fix;
	char overstr=0, paragrafo=1,novaLinha=0, op, bold=0;
	initString(&lstr);
	int qtdCol=0,i, space=0, qtdOver, width=80,l=1, y=0;
	CharToString(ini, &lstr);
	
	width = width - re - rd - pl;
	fix = atual = lstr;
	gotoxy(re, l);
	for(i=0;i < pl; i++)
		printf(" ");
	
	while(atual != NULL)
	{	
		
			
		if(!overstr)							
		{
			
						
			qtdCol = qtdCol + atual->length;
			if(atual->prox != NULL && qtdCol + atual->prox->length > width)				
			{				
				space = width - qtdCol;
				overstr = 1;									
			}
			if(atual->paragrafo)
			{
				novaLinha = 1;									
				overstr =1;
			}							
			if(atual->linha)
				overstr = 1;
					
			
			
		}else{			
			aux = lstr;
			if(paragrafo)
			{
				for(i=0;i < pl; i++)
					printf(" ");
								
				gotoxy(re+pl, l);
				paragrafo=0;
				width += pl;
			}				
			else
				gotoxy(re, l);
			while(aux != NULL && aux != atual)
			{	
				y=wherey();	
				if(y==20)
				{
				   gotoxy(5,23);
				   printf("Pressione qualquer tecla para continuar...\n");
				   getch();
				   limpaTela2();
				   l=1;
				   gotoxy(re,l);
				   y=wherey();
				   
				}
				for(i=0; i<strlen(aux->str); i++)
				{
					if(aux->str[i] == 'з' && bold == 0)
					{
						bold = 1;
					}				
					else if(aux->str[i] == 'з' && bold == 1)
					{
						bold = 0;	
					}				
					else
					{
						if(bold == 1)
						{
							textcolor(1);
						}else
						{
							textcolor(15);
						}			
						printf("%c", aux->str[i]);				
					}
						
				}
				
				printf(" ");
				if(space > 0)
				{
					printf(" ");
					space--;
				}
				
				aux = aux->prox;
				
			}			
			if(aux != NULL)
			{
				for(i=0; i<strlen(aux->str); i++)
				{
					if(aux->str[i] == 'з' && bold == 0)
					{
						bold = 1;
					}				
					else if(aux->str[i] == 'з' && bold == 1)
					{
						bold = 0;	
					}				
					else
					{
						if(bold == 1)
						{
							textcolor(1);
						}else
						{
							textcolor(15);
						}			
						printf("%c", aux->str[i]);				
					}
						
				}
			
				
			}
			printf("\n");
			l++;
			overstr = 0;
			qtdCol = 0;
			lstr = atual->prox;			
			if(novaLinha)
			{
				width = width - pl;
				paragrafo=1;
				novaLinha=0;
			}
		}
		if(!overstr)
		{
			atual = atual->prox;																			
		}
		
		
	}
	
	   gotoxy(5,23);
	   printf("Pressione qualquer tecla para continuar...\n");
	   getch();
	   limpaTela2();	
}

/*  EXIBIR AO PRESSIONAR F5 */

/* Transformar texto em lista de string */



void CharToString(linha *ini, string **lstr)
{
	
	initString(&*lstr);
	
	
	
	linha *aux;
	coluna *auxCursor;
	char strAux[50], paragrafo=0, linha;
	int j = 0;
	aux = ini;
	while(aux != NULL)
	{	
		paragrafo=0;
		linha=0;				
		auxCursor = aux->inicioL;
		j=0;
		while(auxCursor->prox != NULL)
		{	
			
			
			if(auxCursor->letra != 32  && auxCursor->prox->prox != NULL && !paragrafo)
			{
			
				strAux[j] = auxCursor->letra;
				j++;
							
			}								
			else
			{
				if(auxCursor->prox->prox == NULL)
				{
				
					strAux[j] = auxCursor->letra;					
					j++;
					linha=1;
					if(auxCursor->letra == '.')
						paragrafo=1;													
				}
				
				strAux[j] = '\0';															
				j=0;
				
				insereString(&*lstr, strAux, strlen(strAux)+1, paragrafo, linha);
									
			}			
			auxCursor = auxCursor->prox;				
		}		
		aux = aux->bottom;		
	}
}






/* Transformar texto em lista de string */
