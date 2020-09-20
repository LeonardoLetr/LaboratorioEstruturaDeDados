#include <stdio.h>
#include <cstdlib>
#include <stdlib.h>

//Leonardo Rodrigues Batista Geraldo RA:00101457
//Ciencia da Computa��o 4 semestre

struct no {
	int chave;
	struct no* direita;
	struct no* esquerda;
};

typedef struct no* arvore;
int opc;

// Fun��o apenas para inicializar a arvore binaria
arvore inicializar()
{
	return NULL;
}

// Fun��o que que criara um novo N� da arvore e retorna o novo N�
arvore criarNo(int chave)
{
	arvore novo = (arvore) malloc(sizeof(arvore));
	novo->direita = NULL;
	novo->esquerda = NULL;
	novo->chave = chave;
	return novo;
}

// Fun��o para adicionar um novo N� na raiz
// que utiliza recursividade para descobrir a posi��o
// que deve ser inserida
arvore adicionar(arvore raiz, arvore no)
{
	if(raiz == NULL)
	{
		return no;
	}
	else
	{
		if (no->chave < raiz->chave)
		{
			raiz->esquerda = adicionar(raiz->esquerda, no);
		}
		else
		{
			raiz->direita = adicionar(raiz->direita, no);
		}
	}
	
	return raiz;
}


//Fun��o que ira exibir na tela os valores que existem na raiz
// em Pr�-ordem utilizando a raiz de forma recursiva
void exibirArvore(arvore raiz)
{
	if(raiz != NULL)
	{
		printf("(");
		printf("%i", raiz->chave);
		printf(")  ");
		
		exibirArvore(raiz->esquerda);
		exibirArvore(raiz->direita);	
	}
}

// Fun��o que retorna o total de N�s que existem
// usando a raiz para realizar uma fun��o recursiva
// No metodo de busca In-ordem
int qtdNo(arvore raiz)
{
	if (raiz == NULL)
	{
		return 0;
	}
	
	return qtdNo(raiz->esquerda) + 1 + qtdNo(raiz->direita); //In-ordem
	//return qtdNo(raiz->esquerda) + qtdNo(raiz->direita) + 1 //P�s-ordem 
}

// Fun��o usada para buscar um valor especifico na arvore binaria
// utiliza como parametro o valor a ser buscado e a arvore
// para fazer uma busca recursiva
arvore buscar1(int chave, arvore raiz)
{
	if (raiz == NULL)
	{
		return NULL;
	}
	
	if (raiz->chave == chave)
	{
		printf("O valor � a raiz");
		return raiz;
	}
	
	if (raiz->chave > chave)
	{
		return buscar1(chave, raiz->esquerda);
	}
	else 
	{
		return buscar1(chave, raiz->direita);
	}
	
	return NULL;
}

arvore buscar(int chave, arvore raiz, arvore *pai)
{
	arvore atual = raiz;
	*pai = NULL;
	
	while (atual)
	{
		if (atual->chave == chave)
		{
			if (*pai == NULL)
			{
				printf("O valor buscado e uma raiz");
			}
			else 
			{
				if (atual->esquerda == NULL && atual->direita == NULL)
				{
					printf("O valor buscado e uma folha");
				}
				else
				{
					printf("O valor buscado e um no interno");
				}
			}
			return atual;
		}
		
		*pai = atual;
		
		if (chave < atual->chave)
		{
			atual = atual->esquerda;
		}
		else 
		{
			atual = atual->direita;
		}	
	}
	
	return NULL;
}

//Um loop que ira perguntar ao usuario o valor que deseja inserir
//at� que o usuario insira um valor negativo
arvore menuInserir(arvore arv)
{
	int chave = 1, n = 1;
	
	system("cls");
	printf("Digite um valor negativo para finalizar\n");
	
	while(chave >= 0)
	{	
		printf("Valor[%d]: ", n);
		scanf("%d", &chave);
		
		if (chave < 0)	break;
		
		arvore novo = criarNo(chave);
		
		arv = adicionar(arv, novo);	
		n++;
	}
	
	return arv;
}

int main()
{
	arvore arv;
	arvore arvBuscada;
	arvore pai;
	
	arv = inicializar();
	arvBuscada = inicializar();
	pai = inicializar();
	
	do 
	{
		system("cls");
		printf("ARVORE BINARIA\n\n");
		printf("[1] - Inserir Valor\n");
		printf("[2] - Exibir\n");
		printf("[3] - Buscar\n");
		printf("[4] - Quantidade\n");
		printf("[5] - Sair\n\n");
		printf("|");
		
		scanf("%d", &opc);
		
		switch(opc)
		{ 
			case 1: arv = menuInserir(arv);
				break;
				
			case 2: 
				system("cls");
				exibirArvore(arv);
				putchar('\n');
				system("PAUSE");
				break;
				
			case 3:
				system("cls");
				int x;
				
				
				printf("Valor que deseja buscar: ");
				scanf("%d", &x); 
						
				arvBuscada = buscar(x, arv, &pai);
				
				if (arvBuscada != NULL)
					printf("(%d)", arvBuscada->chave);
				else
					printf("Valor n�o encontrado");
				
				putchar('\n');	
				system("PAUSE");
				break;
				
			case 4: 
				system("cls");
				printf("\n\nQuantidade de Valores: %d\n", qtdNo(arv));
				putchar('\n');	
				system("PAUSE");		
				break;
				
			default: printf("Comando invalido!");
		}
		
	} while(opc != 5);

	
	return 0;
}
