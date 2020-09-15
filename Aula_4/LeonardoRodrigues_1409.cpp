#include <stdio.h>
#include <cstdlib>
#include <string.h>

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
arvore criar(int chave)
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
// e agora modificada para n�o ser mais recursiva passando o parametro
// arvore pai que ajudara no loop para buscar aonde est� a chave
arvore buscar(int chave, arvore raiz, arvore *pai)
{
	arvore atual = raiz;
	*pai = NULL;
	
	while (atual)
	{
		if (atual->chave == chave)
		{
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

// Fun��o usada para facilitar o debug da fun��o de remo��o
// para poder tratar melhor as variaveis modificadas
void acompanharRemocao(arvore no, arvore pai, arvore p, arvore q, char *mensagem)
{
	printf("\n\nSTART DEBUG");
	printf("\nno = %d \npai = %d \np = %d \nq = %d", no->chave, pai->chave, p->chave, q->chave);
	
	if (!strcmp(mensagem, "") == 0)		
		printf("\nMensagem = %s", mensagem);
	printf("\n\nSTOP DEBUG");
}

// Funcao usada para remover um valor da nossa arvore, utilizando a chave no metodo busca 
// para retornar sua posi��o e a posi��o pai, utilizei tamb�m as variaveis q e p como auxilio para a manipula��o
// dos valores 
arvore remover(int chave, arvore raiz)
{
	arvore pai, no, p, q;
	
	p = criar(0);
	q = criar(0);
	
	no = buscar(chave, raiz, &pai);
	
	acompanharRemocao(no, pai, p, q, "Valores Iniciais para q e p e depois de N� ter buscado a chave que ira ser removida");
	
	if (no == NULL)
	{
		return raiz;
	}
	
	if(!no->esquerda || !no->direita)
	{
		if(!no->esquerda)
		{
			q = no->direita;
			acompanharRemocao(no, pai, p, q, "q recebe o valor do no a direita");
		} 
		else
		{
			q = no->esquerda;
			acompanharRemocao(no, pai, p, q, "q recebe o valor do no a esquerda");
		} 
	}
	else
	{

		p = no;
		q = no->esquerda;
		
		acompanharRemocao(no, pai, p, q, "p ira receber o valor do nosso no e q o valor a esqueda do n�");
			
		while(q->direita)
		{
			p = q;
			q = q->direita;
			
			acompanharRemocao(no, pai, p, q, "q esta a procura do no mais a direita, ele ira subisituir o valor que esta em p e pegara seus nos filhos");
		}

		if(p != no)
		{
			p->direita = q->esquerda;
			q->esquerda = no->esquerda;
			acompanharRemocao(no, pai, p, q, "promovendo o no mais a direita");
		}
		
		q->direita = no->direita;
	}

	if(!pai)
	{
		free(no);
		acompanharRemocao(no, pai, p, q, "No movido era a raiz");
		return q;
	}
	

	if(chave < pai->chave) 
	{
		pai->esquerda = q;
	}
	else 
	{
		pai->direita = q;
	}
	
	acompanharRemocao(no, pai, p, q, "Finalizando apontando o pai para o q");
	
	free(no);
	return raiz;
}


int main()
{
	arvore arv;
	int chave = 1, n = 1;
	
	arv = inicializar();
	
	arv = adicionar(arv, criar(18));
	arv = adicionar(arv, criar(8));
	arv = adicionar(arv, criar(2));
	arv = adicionar(arv, criar(14));
	arv = adicionar(arv, criar(10));
	arv = adicionar(arv, criar(9));
	arv = adicionar(arv, criar(12));
	arv = adicionar(arv, criar(11));
	arv = adicionar(arv, criar(16));
	
	exibirArvore(arv);
	
	arvore no = remover(14, arv);
	
	putchar('\n\n');
	exibirArvore(arv);
	
	return 0;
}
