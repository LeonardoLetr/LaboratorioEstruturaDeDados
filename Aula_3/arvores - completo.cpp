#include<stdlib.h>
#include<stdio.h>
#define true 1
#define false 0

// Apenas para representar que o valor da chave 
// pode ser qualquer coisa que precisemos, 
// renomeamos o int para usar dentro da estrutura
typedef int TIPOCHAVE;

// Estrutura que representa um n�
typedef struct no{
	TIPOCHAVE chave;
	struct no *esq;
	struct no *dir;
};

// Para simplificar e n�o precisarmos ficar usando a nota��o de ponteiro o tempo todo
// podemos definir um tipo novo para o nosso c�digo
typedef struct no* PONT;

PONT inicializa();
PONT criarNo(int valor);
PONT adiciona (PONT raiz, PONT no);
PONT contem(TIPOCHAVE chave, PONT raiz);
int totalDeNos(PONT raiz);
void exibirArvore(PONT raiz);
PONT buscaNo(PONT raiz, TIPOCHAVE ch, PONT *pai);
PONT removeNo(TIPOCHAVE ch, PONT raiz);

int main (){
	PONT r = inicializa();
	PONT novo = criarNo(15);
	r = adiciona(r, novo);
	novo = criarNo(8);
	r = adiciona(r, novo);
	
	printf("Valor: %d", r->chave);
	PONT busca = contem(15,r);
	printf("Valor: %d", busca->chave);
	printf("Total raiz: %d", totalDeNos(r));
	printf("\n\n");
	exibirArvore(r);
	printf("\n\n");
	r  = removeNo(8, r);
	exibirArvore(r);
	
	return 0;
}

// Inicializa  �rvore, como no nosso caso a raiz ser� o primeiro 
// elemento, ent�o ela simplesmente retorna null
PONT inicializa(){
	return(NULL);
}

// Cria um novo n� com o valor de chave passado como par�metro
PONT criarNo(int valor){
	PONT novo = (PONT) malloc(sizeof(PONT));
	novo->chave = valor;
	novo->esq = NULL;
	novo->dir = NULL;
}

// Como conven��o teremos que n�o temos chaves repetidas.
// Como a ideia � buscar elementos, n�o faz muito sentido
// buscarmos coisas repetidas, identificadores devem ser unicos.
PONT adiciona (PONT raiz, PONT no){
	//Se a raiz for null, inserimos l�
	if(raiz == NULL) return no;
	//Sen�o
	else{
		// Se a chave do elemento a ser inserido for menor que a da raiz: insere na subarvore da esquerda
		if(no->chave < raiz->chave)
			raiz->esq = adiciona(raiz->esq, no);
		//Sen�o, insere na subararvore da direita.
		else
			raiz->dir = adiciona(raiz->dir, no);
	}
	
	return raiz;
}

// Busca uma chave na arvore
PONT contem(TIPOCHAVE chave, PONT raiz){
	// Se a raiz for null, n�o temos onde procurar
	if(raiz == NULL) return NULL;
	// Se a chave buscada for a chave da raiz, j� encontramose retornamos a propria raiz
	if(raiz->chave == chave) return raiz;
	// Se a chave buscada for menor que a chave da raiz, buscamos na subarvore da esquerda
	if(raiz->chave > chave)
		return contem(chave, raiz->esq);
	
	//Sen�o, fazemos a busca na subarvore da direita
	return contem(chave, raiz->dir);	
}

// Busca bin�ria n�o recursiva, para que possamos ter o pai do n� cuja chave n�s procuramos
// fun��o auxiliar para a remo��o
PONT buscaNo(PONT raiz, TIPOCHAVE ch, PONT *pai){
	// Variavel auxiliar para a itera��o da arvore
	PONT atual = raiz;
	// Como � um ponteiro para PONT, acaba sendo que essa variavel � um ponteiro para ponteiro.
	//Arqui vamos armazenar o endere�o do pai do elemento buscado
	*pai = NULL;
	// Enquanto atual for v�lido
	while(atual){
		// se o elemento buscado for o atual, ent�o retornamos o elemento. Como o pai � um ponteiro
		// e alteramos ele diretamente, ele n�o precisa ser retornado
		if(atual->chave == ch) return atual;
		// Caso o elemento atual n�o seja o que estamos buscando, atualizamos o pai para ser igual
		// o elemento atual, para podermos continuar indo pela subarvore da esquerda ou da direita
		*pai = atual;
		// se a chave buscada for menor que do elemento atual, buscamos pela subarvore da esquerda
		if(ch < atual->chave) atual = atual->esq;
		// caso contrario buscamos pela subarvore da direita.
		else atual = atual->dir;
	}
	return NULL;
}

// Remover um n� da arvore em qualquer posi��o
// Para a remo��o precisamos garantir que a propriedades da arvore binaria ainda sejam v�lidas.
PONT removeNo(TIPOCHAVE ch, PONT raiz){
	PONT pai, no, p, q;
	no = buscaNo(raiz, ch, &pai);
	if(no == NULL) return raiz;
	// Aqui tratamos o caso de o n� a ser removido ter apenas um filho
	if(!no->esq || !no->dir){
		if(!no->esq) q = no->dir;
		else q = no->esq;
	}
	// Aqui tratamos o caso do n� ter os dois filhos
	else{
		// Se chegamos aqui, � porque o n� a aser buscado tem as duas subarvores
		// Nesse caso precisamos ir o mais a direita poss�vel na subarvore da esquerda 
		// do no a ser removido. Nesse processo, sempre marcamos quem � o n� a direita e 
		// o pai dele. Isso porque quiando chegarmos no elemento mais a direita, 
		// teremos que fazer o pai dele "adotar" seus filhos, uma vez que o no mais a direita
		// ser� "promovido" para a posi��o do o no sendo removido
		p = no;
		q = no->esq;
		while(q->dir){
			p = q;
			q = q->dir;
		}
		
		// Depois que encontramos o n� mais a esquerda, precisamos modificar os ponteiros para 
		// que eles possam promover o no mais a direita e fazer a promo��o do no mais a direita da 
		// subarvore da esquerda
		if(p != no){
			p->dir = q->esq;
			q->esq = no->esq;
		}
		
		q->dir = no->dir;
	}
	
	// Aqui tratamos se o n� a ser movido � a raiz
	if(!pai){
		free(no);
		return q;
	}
	
	// Aqui tratamos se o n� a ser removido n�o for a raiz
	if(ch < pai->chave) pai->esq = q;
	else pai->dir = q;
	free(no);
	return raiz;
	
}

// Contagem do total de n�s na �rvore
int totalDeNos(PONT raiz){
	// Se a raiz for null, n�o temos n� nenhum, logo total � 0
	if(raiz == NULL) return 0;
	
	// Caminhamos pela subarvore da esquerda, quando voltamos para raiz, contamos ela
	// e depois vamos para subarvore da direita.
	// Aqui percebemos explicitamente que percorremos a �rovre in-ordem.
	// Podemos alterar o m�todo percorre-la e n�o vai influenciar na contagem,
	// mas se percorrermos para a impress�o dos dados da �rvore, por exemplo,
	// cada modo de percorrer produzir� um resultado diferente.
	return totalDeNos(raiz->esq) + 1 + totalDeNos(raiz->dir);
	
}

// Nessa exibi��o usamos a nota��o onde usamos parenteses para agrupar as �rvores e suas 
// suarvores
void exibirArvore(PONT raiz){
	if(raiz != NULL){
		printf("%i", raiz->chave);
		printf("(");
		exibirArvore(raiz->esq);
		exibirArvore(raiz->dir);
		printf(")");
	}
}
