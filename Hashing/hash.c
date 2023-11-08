struct hash{
	int k, pos;
	struct hash *prox;
};
typedef struct hash Hash;


struct tpReg{
	int cod;
	char status, nome[40];	
};
typedef struct tpReg TpReg;



void inserirArquivo()
{
	TpReg reg;	
	
	printf("Cod: \n");
	while(scanf("%d", &reg.cod) != 0)
	{
		pos = BuscaCod(reg.cod);
		printf("Nome: \n");
		fflush(stdin);
		gets(reg.nome);
		reg.status = '1';
		printf("Cod: \n");	
	}
}
