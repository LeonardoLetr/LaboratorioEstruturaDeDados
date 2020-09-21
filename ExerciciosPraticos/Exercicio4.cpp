#include <stdio.h>
#include <cstdlib>

//Leonardo Rodrigues Batista Geraldo RA:00101457
//Ciencia da Computação 4 semestre

struct no {
	int chave;
	struct no* direita;
	struct no* esquerda;
};

typedef struct no arvore;

// Função apenas para inicializar a arvore binaria
arvore* inicializar()
{
	return NULL;
}

// Função que que criara um novo Nó da arvore e retorna o novo Nó
arvore* criarNo()
{
	arvore* novo = (arvore*) malloc(sizeof(arvore));
}

int main()
{
	arvore* arv;
	
	arv = inicializar();
	
	return 0;
}
