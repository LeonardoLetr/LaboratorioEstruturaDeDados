#include <stdio.h>
#include <cstdlib>

//Leonardo Rodrigues Batista Geraldo RA:00101457
//Ciencia da Computa��o 4 semestre

struct no {
	int chave;
	struct no* direita;
	struct no* esquerda;
};

typedef struct no* arvore;

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
arvore buscar(int chave, arvore raiz)
{
	if (raiz == NULL)
	{
		return NULL;
	}
	
	if (raiz->chave == chave)
	{
		return raiz;
	}
	
	if (raiz->chave > chave)
	{
		return buscar(chave, raiz->esquerda);
	}
	
	return buscar(chave, raiz->direita);
}

int main()
{
	arvore arv;
	int chave = 1, n = 1;
	
	arv = inicializar();
	
	printf("ARVORE BINARIA\n\n");
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
	
	printf("\n\nQuantidade de Valores: %d\n", qtdNo(arv));
	
	exibirArvore(arv);
	
	return 0;
}
