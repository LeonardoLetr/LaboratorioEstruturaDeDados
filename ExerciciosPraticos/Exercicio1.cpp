#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <cstdlib>
#include <string.h>

//Leonardo Rodrigues Batista Geraldo RA:00101457
//Ciencia da Computa��o 4 semestre

struct no {

	int value;                 
	struct no* next;      
};

typedef struct no* List;

// Fun��o apenas para inicializar a lista
List build() {
    return NULL;
}

// Fun��o que ira inserir um novo no na lista para isso
// � criado uma novo no que ira guardar o valor passado no parametro
// e gurda no proximo a lista que j� existe
List insert(List l, int i)
{
    List newList = (List) malloc(sizeof(List));
    newList->value = i;
    newList->next = l;
    
    return newList;
}

// Fun��o para verificar se aquele no contem algum valor
int isEmpty(List l)
{
	return l == NULL;
}


// Fun��o recursiva que ficara exibindo na tela o valor da lista atual
// e depois chamara a fun��o de novo passando como parametro o no que se encontra na variavel proximo
void showList(List l) 
{

    if(!isEmpty(l))
	{
    	printf("%d  ", l->value);
    	showList(l->next);
	}
}

// Fun��o recursiva para retornar os valores de Fibonacci
// Tem como parametros a posi��o que o usuario deseja extrair da sequencia
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

// Fun��o quer ira inverter a lista
// y representa a ultima referencia da lista, que ira passar para r como o primeiro valor
List reverseList (List l)
{
	List t; 
	List y = l; 
	List r = NULL;
	
    while (y != NULL) 
	{ 
       t = y->next; 
       y->next = r; 
       r = y; 
       y = t; 
    }    
    return r;
}

int main()
{
	int n;
	
	printf("Deseja exibir quantos valores: ");
	scanf("%d", &n);
	
	
	List lista;
	
	lista = build();

	
	for (int i = n; i != 0; i--)
	{
		int fibo = fibonacci(i);
		lista = insert(lista, fibo);
	}
	
	char escolha[10];
	printf("Exibit Crescente ou Descresente? (C/D)  ");
	scanf("%s", escolha);

	putchar('\n');
	if (strcmp (escolha, "C") == 0)
	{
		showList(lista);
	}
	else 
	{
		lista = reverseList(lista);
		showList(lista);
	}
	
	return 0;
}



