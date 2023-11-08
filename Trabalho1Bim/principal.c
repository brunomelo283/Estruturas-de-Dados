#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include "tad.h"


void Menu()
{
	int x, y;
	gotoxy(4,2);
	printf("F2 - ABRIR");
	gotoxy(24,2);
	printf("F3 - SALVAR");
	gotoxy(44,2);
	printf("F4 - SAIR");
	gotoxy(64,2);
	printf("F5 - EXIBIR");
	gotoxy(1,3);
	printf("-------------------------------------------------------------------------------");
	gotoxy(1,21);
	printf("-------------------------------------------------------------------------------");
	gotoxy(4,22);
	printf("COL: ");	
	gotoxy(14,22);
	printf("LIN: ");	
	gotoxy(24,22);
	printf("INSERT");
	gotoxy(34,22);
	printf("|||");
	gotoxy(1,4);
	x = wherex();
	y = wherey();
	gotoxy(8, 22);
	printf("%02d", x );
	gotoxy(18, 22);
	printf("%02d", y-3);
	gotoxy(x, y);
}

void limpaRecomenda()
{
	int auxj=0;
	while(auxj < 20)
	{
		gotoxy(41+auxj, 22);
		printf("%c", NULL);
		auxj++;
	}
}

int main(){
	char op, nomearq[50], letras[50], palavra[50], recomendar, opcao;
	int flagQuit = 0, flagInsert = 0,x,y,pl,re,rd, minl=0, maxl=2, i,j=0;
	linha *lin, *ini, *page;
	ListaGen *lpalavras = NULL;
	coluna *col;
	initLinha(&lin);
	initLinha(&ini);
	initColuna(&col);	
	criaLinha(&ini, &lin, &col);
	page = ini;
	FILE *ptrArq;
	Menu();
	do{
		
		op = getch();
		if(op == 0)
		{
			op = getch();
			switch(op)	
			{
				case 60: 
					//F2	
					limpaTela();											
					gotoxy(15, 8);
					printf("Informe o nome do arquivo");
					gotoxy(15, 10);
					fflush(stdin);
					scanf("%s", &nomearq);					
					Menu();
					gotoxy(15, 8);
					printf("Tem certeza que deseja abrir o arquivo?");					
					gotoxy(15, 10);
					printf("Obs: Abrir o arquivo ira sobrescrever ");
					gotoxy(16, 11);
					printf("todo texto digitado");
					gotoxy(18, 15);
					printf("S - [SIM]\t\tN - [NAO]");
					opcao =	toupper(getch());				
					if(opcao == 'S')
					{
						destroyStruct(&ini);
						initLinha(&lin);
						initLinha(&ini);
						initColuna(&col);	
						criaLinha(&ini, &lin, &col);
						openFile(ptrArq, nomearq,&ini, &lin, &col, &page);
						col = ini->inicioL;	
						lin = ini;
						page = ini;
						x=1; y=4;
							
					}
					ajustarTela(ini,col, &page,x, y, flagInsert);												
					break;
				case 61:
					//F3
					gotoxy(2, 19);
					printf("Informe o nome do arquivo");
					gotoxy(2, 20);
					fflush(stdin);
					scanf("%s", &nomearq);
					saveFile(ptrArq, nomearq, ini);
					printf("F3\n");
					break;
				case 62:
					//F4
					flagQuit = 1;				
					break;
				case 63:
					//F5
					x = wherex();
					y = wherey();
					gotoxy(1,4);
					//exibirTexto(ini);
					limpaTela();
					gotoxy(15,8);
					printf("Configuracao dos paragrafos");
					gotoxy(15, 11);
					printf("Primeira Linha: ");
					gotoxy(15, 14);
					printf("Recuo Esquerdo: ");
					gotoxy(15, 17);
					printf("Recuo Direito: ");					
					gotoxy(35, 11);
					scanf("%d", &pl);
					gotoxy(35, 14);
					scanf("%d", &re);
					gotoxy(35, 17);
					scanf("%d", &rd);					
					clrscr();
					JustifyText(ini, pl,re,rd);
					Menu();					
					ajustarTela(ini, col, &page, x, y, flagInsert);
					break;
				case 68:
					//F10	
					criaColuna(&col, &lin, &ini, &page, '§', flagInsert);	
					ajustarTela(ini, col, &page, wherex(), wherey(), flagInsert);			
					break;			
			}
		}else if(op == -32){
			op = getch();
			switch(op)
			{
				case 71: 
					//Home
					moveCursorLinha(op,  &lin,&page, &col);
					ajustarTela(ini, col, &page,wherex(), wherey(), flagInsert);					
					break;
				case 79:
					//END
					moveCursorLinha(op, &lin,&page, &col);
					ajustarTela(ini, col, &page,wherex(), wherey(), flagInsert);					
					break;
				case 73:
					//PGUP
					moveCursorLinha(op, &lin,&page, &col);
					ajustarTela(ini, col, &page,wherex(), wherey(), flagInsert);					
					break;
				case 81:					
					//PGDOWN
					moveCursorLinha(op, &lin,&page, &col);
					ajustarTela(ini, col, &page,wherex(), wherey(), flagInsert);					
					break;
				case 83:
					//DELETE
					deleteChar(op, &lin, &col, ini, &page, flagInsert);
					ajustarTela(ini,col, &page, wherex(), wherey(), flagInsert);
					break;
				case 82:
					//INSERT
					x = wherex();
					y = wherey();
					if(flagInsert == 0)					
					{					
						flagInsert = 1;																								
						gotoxy(24,22);
						textcolor(4);
						printf("INSERT");
						textcolor(15);
						gotoxy(x,y);												
					}						
					else
					{
						flagInsert = 0;	
						gotoxy(24,22);
						textcolor(15);				
						printf("INSERT");
						gotoxy(x,y);						
					}
						
					ajustarTela(ini,col, &page, wherex(), wherey(), flagInsert);
					break;
				case 72: 
					//SETA PARA CIMA  
					moveCursorLinha(op, &lin, &page, &col);
					ajustarTela(ini, col, &page, wherex(), wherey(), flagInsert);					
					break;
				case 77:
					//SETA PARA DIREITA   				
					moveCursorLinha(op, &lin, &page, &col);				
					ajustarTela(ini, col, &page, wherex(), wherey(), flagInsert);					
					break;
				case 80:
					//SETA PARA BAIXO   
					moveCursorLinha(op, &lin, &page, &col);
					ajustarTela(ini,col,&page,  wherex(), wherey(), flagInsert);					
					break;
				case 75:
					//SETA PARA ESQUERDA   
					moveCursorLinha(op, &lin, &page,&col);
					ajustarTela(ini, col, &page, wherex(), wherey(), flagInsert);
					break;
				
			
			}
		}else if(op == 8){
			deleteChar(op, &lin, &col, ini, &page, flagInsert);
			if(j> 0)
				j--;
			//ajustarTela(ini,col, wherex(), wherey(), flagInsert);			
		}else if(op == 9){
			
			moveCursorLinha(79, &lin, &page,&col);
			for(i=j; i < strlen(palavra);i++)
			{
				criaColuna(&col, &lin, &ini, &page, palavra[i], flagInsert);							
			}
			ajustarTela(ini,col, &page,lin->nro+1, wherey(), flagInsert);	
			j=0;
			letras[j] = '\0';
			palavra[0] = '\0';
			
		}
		else if(op == 13){	
			criaLinha(&ini, &lin, &col);		
			printf("\n");			
			x = wherex();
			y = wherey();
			ajustarTela(ini,col, &page, x,y, flagInsert);
			x = wherex();
			y = wherey();
			gotoxy(8, 22);
			printf("%02d", x);		
			gotoxy(x, y);
			letras[j] = '\0';
			if(strcmp(letras, "\0") != 0)
				inserePalavra(&lpalavras, letras);
			j=0;
			x = wherex();
			y = wherey();
			limpaRecomenda();		
			gotoxy(x, y);			
		}else if(op == 32){						
			criaColuna(&col, &lin, &ini, &page, op, flagInsert);
			letras[j] = '\0';
			if(strcmp(letras, "\0") != 0)
				inserePalavra(&lpalavras, letras);
			j=0;
			ajustarTela(ini,col, &page, wherex()+1, wherey(),flagInsert);
			x = wherex();
			y = wherey();
			limpaRecomenda();		
			gotoxy(x, y);
		}		
		else{			
			printf("%c", op);			
			criaColuna(&col, &lin, &ini, &page, op, flagInsert);
			x = wherex();
			y = wherey();
			limpaRecomenda();		
			gotoxy(x, y);
			letras[j] = op;
			j++;
			letras[j] = '\0';
			recomendar = buscaPalavra(lpalavras, letras, palavra);
			if(recomendar)
			{
				x = wherex();
				y = wherey();
				gotoxy(42, 22);
				printf("%s", palavra);
				gotoxy(x, y);
			}
			ajustarTela(ini,col, &page,wherex(), wherey(), flagInsert);							
		}
		
	}while(flagQuit == 0);
	return 0;
}
