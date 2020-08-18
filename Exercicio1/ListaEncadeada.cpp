#include <stdio.h>
#include <cstdlib>

// Leonardo Rodrigues Batista Geraldo RA: 00101457

struct no {
	int valor;
	struct no* proximo;
};

typedef struct no lista;

// Função apenas para inicializar a lista
lista* inicializar()
{
	return NULL;
}

// Função que ira inserir um novo no na lista para isso
// é criado uma novo no que ira guardar o valor passado no parametro
// e gurda no proximo a lista que já existe
lista* inserir(lista* l, int valor)
{
	lista* novo = (lista*) malloc(sizeof(lista));
	
	novo->valor	= valor;
	novo->proximo = l;
	
	return novo;
}

// Função para verificar se aquele no contem algum valor
int isEmpty(lista *l)
{
	return l == NULL;
}

// Função recursiva que ficara exibindo na tela o valor da lista atual
// e depois chamara a função de novo passando como parametro o no que se encontra na variavel proximo
void vizualizar(lista* l)
{
	if (!isEmpty(l))	
	{
		printf("%d ", l->valor);
		vizualizar(l->proximo);
	}
}

// Função recursiva para retornar os valores de Fibonacci
// Tem como parametros a posição que o usuario deseja extrair da sequencia
int fibonacci(int pos)
{
	if (pos == 1 || pos == 2)
	{
		return 1;
	}
	else
	{
		return fibonacci(pos-1) + fibonacci(pos-2);
	}
}

int main()
{
	int n;
	
	printf("Deseja exibir quantos valores: ");
	scanf("%d", &n);
	
	lista* lista;
	
	lista = inicializar();
	
	for (int i = n; i != 0; i--)
	{
		int fibo = fibonacci(i);
		lista = inserir(lista, fibo);
	}

	
	vizualizar(lista);
	
	return 0;
}

