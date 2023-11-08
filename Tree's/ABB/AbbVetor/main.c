#include<stdio.h>
#include<conio2.h>
#include<windows.h>

#define TF 350



struct pilha{
	int pos;
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

void push(Pilha **p, int pos)
{
	Pilha *nova = (Pilha*)malloc(sizeof(Pilha));
	nova->pos = pos;
	nova->prox = *p;
	*p = nova;
}

void pop(Pilha **p, int *pos)
{
	Pilha *aux;
	if(!isEmpty(*p))
	{
		*pos = (*p)->pos;	
		aux = (*p)->prox;
		free(*p);
		*p = aux;		
	}else{
		*pos = -1;
	}
}

void pre_ordem(int vet[TF],int TL)
{
	if(vet[TL] != 0)
	{
		printf("%d - ", vet[TL]);
		pre_ordem(vet, TL*2+1);
		pre_ordem(vet, TL*2+2);
	}
}


void in_ordem(int vet[TF], int TL)
{
	if(vet[TL] != 0)
	{		
		in_ordem(vet, TL*2+1);
		printf("%d - ", vet[TL]);
		in_ordem(vet, TL*2+2);
	}
}

void pos_ordem(int vet[TF], int TL)
{
	if(vet[TL] != 0)
	{		
		pos_ordem(vet, TL*2+1);		
		pos_ordem(vet, TL*2+2);
		printf("%d - ", vet[TL]);
	}
}


void pre_ordem_iterativo(int vet[TF], int TL)
{
	Pilha *p;
	init(&p);
	push(&p, TL);
	
	while(!isEmpty(p))
	{
		if(vet[TL] != 0)
		{
			pop(&p, &TL);
			while(vet[TL] != 0)
			{		
				printf(" -%d- ", vet[TL]);		
				push(&p, TL);
				TL = TL*2+1;
			}
			
		}
		pop(&p, &TL);
		TL = TL*2+2;
		if(vet[TL] != 0)
			push(&p, TL);
	}
}

void in_ordem_iterativo(int vet[TF], int TL)
{
	Pilha *p;
	init(&p);
	push(&p, TL);
	
	while(!isEmpty(p))
	{
		if(vet[TL] != 0)
		{
			pop(&p, &TL);
			while(vet[TL] != 0)
			{
							
				push(&p, TL);
				TL = TL*2+1;
			}
		}
		
		pop(&p, &TL);
		printf(" -%d- ", vet[TL]);	
		TL = TL*2+2;
		if(vet[TL] != 0)
			push(&p, TL);
	}
}



void pos_ordem_iterativo(int vet[TF], int TL)
{
	Pilha *p;
	Pilha *p2;
	init(&p);
	init(&p2);
	push(&p, TL);
	
	while(!isEmpty(p))
	{
		if(vet[TL] != 0)
		{
			pop(&p, &TL);
			while(vet[TL] != 0)
			{				
				push(&p2, TL);
				push(&p, TL);			
				TL = TL*2+2;
			}
		}
		
		pop(&p, &TL);		
		TL = TL*2+1;
		if(vet[TL] != 0)
			push(&p, TL);
	}
	
	while(!isEmpty(p2))
	{
		pop(&p2, &TL);
		printf(" -%d- ", vet[TL]);
	}
}

void exibir(int vet[TF],int TL, int x, int y, int dist)
{
	if(vet[TL] != 0)
	{
		gotoxy(x, y), printf("%d", vet[TL]);
		y++;
		if(vet[TL*2+1] != 0)
			gotoxy(x- dist/2,y), printf("/");	
		exibir(vet,TL*2+1, x-dist, y+1, dist/2);
		if(vet[TL*2+2] != 0)
			gotoxy(x+dist/2, y), printf("\\");		
		exibir(vet, TL*2+2,x+dist, y+1, dist/2);
	}
}

void BuscaAbb(int vet[TF],int TL,int *pos, int info)
{
	if(vet[TL] != 0)
	{
		if(vet[TL] == info)
			*pos = TL;
		else
		{
			if(*pos == -1)
				BuscaAbb(vet,TL*2+1, &*pos, info);
			if(*pos == -1)
				BuscaAbb(vet,TL*2+2, &*pos, info);
		}
	}
}

void BuscaAbbPai(int vet[TF],int TL, int TLAnt,int *e, int *pai, int info)
{
	if(vet[TL] != 0)
	{
		if(vet[TL] == info)
		{
			*e = TL;
			*pai = TLAnt;
		}
			
		else
		{
			if(*e == -1)
				BuscaAbbPai(vet,TL*2+1, TL, &*e, &*pai, info);
			if(*e == -1)
				BuscaAbbPai(vet,TL*2+2, TL,&*e, &*pai, info);
		}
	}
}
void pre_ordem_pilha(int vet[TF], int TL, Pilha **p)
{
	if(vet[TL] != 0)
	{
		push(&*p, TL);
		pre_ordem_pilha(vet, TL*2+1, &*p);
		pre_ordem_pilha(vet, TL*2+2, &*p);
	}
}
void exclusao(int vet[TF], int TLE, int TLPai)
{
	int paiSub, sub, aux, TLAux, TLAuxp, i;
	Pilha *p;
	init(&p);
	char flagE=1;		
	if(vet[TLE*2+1] == 0 && vet[TLE*2+2] == 0)
	{
		//é folha
		if(TLE != TLPai)
		{
			if(vet[TLE] > vet[TLPai])
				vet[TLPai*2+2] = 0;
			else
				vet[TLPai*2+1] = 0;
		}
		else
			vet[TLE] = 0;
	}
	else
	{
		if(vet[TLE*2+1] == 0 || vet[TLE*2+2] == 0)
		{ //um filho
			if(TLE != TLPai)
			{
				aux = vet[TLE];
				vet[TLE] = 0;
				if(vet[TLE*2*1] != 0)
					TLE = TLE *2 + 1;
				else
				TLE = TLE *2 + 2;
				pre_ordem_pilha(vet, TLE, &p);
				while(!isEmpty(p))
				{
					pop(&p, &TLAux);
					printf("[%d]\t", TLAux);
				}
//				while(flagE)
//				{		
//					flagE=0;
//																								
//					if(vet[TLE*2+2] != 0)
//					{
//						if(vet[TLE*2+2] > vet[TLPai])
//							vet[TLPai*2+2] = vet[TLE*2+2];
//						else
//							vet[TLPai*2+1] = vet[TLE*2+2];
//						vet[TLE*2+2] = 0;
//						TLPai = TLE;
//						TLE = TLE*2+2;
//						flagE=1;
//					}								
//					else
//					{	
//						if(vet[TLE*2+1] != 0)
//						{
//							if(vet[TLE*2+1] > vet[TLPai])
//								vet[TLPai*2+2] = vet[TLE*2+1];
//							else
//								vet[TLPai*2+1] = vet[TLE*2+1];
//							vet[TLE*2+1] = 0;
//							TLPai = TLE;
//							TLE = TLE*2+1;
//							flagE=1;
//						}							
//						
//					}
//						
//				}																			
			}
			else			
			{
				if(vet[TLE*2+2] != 0)
				{
					vet[TLPai] = vet[TLE*2+2];
					TLE = TLE *2+2;
				}				
						
				else
				{
					vet[TLPai] = vet[TLE*2+1];
					TLE = TLE *2+1;
				}
				exclusao(vet, TLE, TLPai);
				
					
																
			}
		}else
		{//dois filhos
			paiSub =  TLE;
			sub = TLE*2+2;
			while(vet[sub*2+1] != 0)
			{
				paiSub = sub;
				sub = sub*2+1;
			}
			aux = vet[sub];
			exclusao(vet, sub, paiSub);
			vet[TLE] = aux;
		}
	}
	
}

int main(void){
	int vet[TF] = {0};
	int num, TL=0, TLAnt, i,info,pos=-1, TLE=-1,TLPai=-1;	
	
	printf("Informe um elemento para inserir na arvore: ");
	scanf("%d", &info);
	vet[TL] = info;
	while(info != 0)
	{
		
		TL=0;
		printf("Informe um elemento para inserir na arvore: ");
		scanf("%d", &info);	
		while(vet[TL] != 0)
		{
			TLAnt = TL;
			if(info < vet[TL])
				TL = TL*2+1;
			else
				TL = TL*2+2;
		}
		
		if(info < vet[TLAnt])
			vet[TL] = info;
		else
			vet[TL] = info;
	}
//	pre_ordem(vet, 0);
//	getch();
//	printf("\n");
//	in_ordem(vet, 0);
//	getch();
//	printf("\n");
//	pos_ordem(vet, 0);
//	getch();
//	printf("\n");
//	pre_ordem_iterativo(vet, 0);
//	printf("\n");
//	printf("\n");
//	getch();
//	in_ordem_iterativo(vet, 0);
//	getch();
//	printf("\n");
//	printf("\n");
//	pos_ordem_iterativo(vet, 0);

	system("cls");
	exibir(vet, 0, 40,1,20);
	getch();
	
//	system("cls");	
//	pos=-1;
//	printf("Informe o elemento que deseja buscar: \n");
//	scanf("%d", &info);
//	BuscaAbb(vet,0, &pos, info);
//	if(pos != -1)
//		printf("Elemento [%d] encontrado na posicao [%d]\n", vet[pos], pos);		
//	else
//		printf("Elemento nao encontrado\n");
	while(1)
	{
		TLE=TLPai=-1;
		system("cls");
		printf("Informe o elemento que deseja remover da arvore:\n");
		scanf("%d", &info);
		BuscaAbbPai(vet, 0,0, &TLE, &TLPai, info);
		//printf("Elemento [%d] encontrado nas pos[%d] com pai [%d] nas pos[%d]\n",vet[TLE], TLE, vet[TLPai], TLPai);
		exclusao(vet,TLE, TLPai);
		system("cls");
		exibir(vet, 0, 40,1,20);
		getch();	
	}
	
	return 0;
}
