#include <stdio.h>
#include <cstdlib>

//Leonardo Rodrigues Batista Geraldo RA:00101457
//Ciencia da Computa��o 4 semestre

struct no {
	int chave;
	struct no* direita;
	struct no* esquerda;
};

typedef struct no arvore;

// Fun��o apenas para inicializar a arvore binaria
arvore* inicializar()
{
	return NULL;
}

// Fun��o que que criara um novo N� da arvore e retorna o novo N�
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
