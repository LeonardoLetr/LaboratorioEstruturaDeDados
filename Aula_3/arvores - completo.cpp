#include<stdlib.h>
#include<stdio.h>
#define true 1
#define false 0

// Apenas para representar que o valor da chave 
// pode ser qualquer coisa que precisemos, 
// renomeamos o int para usar dentro da estrutura
typedef int TIPOCHAVE;

// Estrutura que representa um nó
typedef struct no{
	TIPOCHAVE chave;
	struct no *esq;
	struct no *dir;
};

// Para simplificar e não precisarmos ficar usando a notação de ponteiro o tempo todo
// podemos definir um tipo novo para o nosso código
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

// Inicializa  árvore, como no nosso caso a raiz será o primeiro 
// elemento, então ela simplesmente retorna null
PONT inicializa(){
	return(NULL);
}

// Cria um novo nó com o valor de chave passado como parâmetro
PONT criarNo(int valor){
	PONT novo = (PONT) malloc(sizeof(PONT));
	novo->chave = valor;
	novo->esq = NULL;
	novo->dir = NULL;
}

// Como convenção teremos que não temos chaves repetidas.
// Como a ideia é buscar elementos, não faz muito sentido
// buscarmos coisas repetidas, identificadores devem ser unicos.
PONT adiciona (PONT raiz, PONT no){
	//Se a raiz for null, inserimos lá
	if(raiz == NULL) return no;
	//Senão
	else{
		// Se a chave do elemento a ser inserido for menor que a da raiz: insere na subarvore da esquerda
		if(no->chave < raiz->chave)
			raiz->esq = adiciona(raiz->esq, no);
		//Senão, insere na subararvore da direita.
		else
			raiz->dir = adiciona(raiz->dir, no);
	}
	
	return raiz;
}

// Busca uma chave na arvore
PONT contem(TIPOCHAVE chave, PONT raiz){
	// Se a raiz for null, não temos onde procurar
	if(raiz == NULL) return NULL;
	// Se a chave buscada for a chave da raiz, já encontramose retornamos a propria raiz
	if(raiz->chave == chave) return raiz;
	// Se a chave buscada for menor que a chave da raiz, buscamos na subarvore da esquerda
	if(raiz->chave > chave)
		return contem(chave, raiz->esq);
	
	//Senão, fazemos a busca na subarvore da direita
	return contem(chave, raiz->dir);	
}

// Busca binária não recursiva, para que possamos ter o pai do nó cuja chave nós procuramos
// função auxiliar para a remoção
PONT buscaNo(PONT raiz, TIPOCHAVE ch, PONT *pai){
	// Variavel auxiliar para a iteração da arvore
	PONT atual = raiz;
	// Como é um ponteiro para PONT, acaba sendo que essa variavel é um ponteiro para ponteiro.
	//Arqui vamos armazenar o endereço do pai do elemento buscado
	*pai = NULL;
	// Enquanto atual for válido
	while(atual){
		// se o elemento buscado for o atual, então retornamos o elemento. Como o pai é um ponteiro
		// e alteramos ele diretamente, ele não precisa ser retornado
		if(atual->chave == ch) return atual;
		// Caso o elemento atual não seja o que estamos buscando, atualizamos o pai para ser igual
		// o elemento atual, para podermos continuar indo pela subarvore da esquerda ou da direita
		*pai = atual;
		// se a chave buscada for menor que do elemento atual, buscamos pela subarvore da esquerda
		if(ch < atual->chave) atual = atual->esq;
		// caso contrario buscamos pela subarvore da direita.
		else atual = atual->dir;
	}
	return NULL;
}

// Remover um nó da arvore em qualquer posição
// Para a remoção precisamos garantir que a propriedades da arvore binaria ainda sejam válidas.
PONT removeNo(TIPOCHAVE ch, PONT raiz){
	PONT pai, no, p, q;
	no = buscaNo(raiz, ch, &pai);
	if(no == NULL) return raiz;
	// Aqui tratamos o caso de o nó a ser removido ter apenas um filho
	if(!no->esq || !no->dir){
		if(!no->esq) q = no->dir;
		else q = no->esq;
	}
	// Aqui tratamos o caso do nó ter os dois filhos
	else{
		// Se chegamos aqui, é porque o nó a aser buscado tem as duas subarvores
		// Nesse caso precisamos ir o mais a direita possível na subarvore da esquerda 
		// do no a ser removido. Nesse processo, sempre marcamos quem é o nó a direita e 
		// o pai dele. Isso porque quiando chegarmos no elemento mais a direita, 
		// teremos que fazer o pai dele "adotar" seus filhos, uma vez que o no mais a direita
		// será "promovido" para a posição do o no sendo removido
		p = no;
		q = no->esq;
		while(q->dir){
			p = q;
			q = q->dir;
		}
		
		// Depois que encontramos o nó mais a esquerda, precisamos modificar os ponteiros para 
		// que eles possam promover o no mais a direita e fazer a promoção do no mais a direita da 
		// subarvore da esquerda
		if(p != no){
			p->dir = q->esq;
			q->esq = no->esq;
		}
		
		q->dir = no->dir;
	}
	
	// Aqui tratamos se o nó a ser movido é a raiz
	if(!pai){
		free(no);
		return q;
	}
	
	// Aqui tratamos se o nó a ser removido não for a raiz
	if(ch < pai->chave) pai->esq = q;
	else pai->dir = q;
	free(no);
	return raiz;
	
}

// Contagem do total de nós na árvore
int totalDeNos(PONT raiz){
	// Se a raiz for null, não temos nó nenhum, logo total é 0
	if(raiz == NULL) return 0;
	
	// Caminhamos pela subarvore da esquerda, quando voltamos para raiz, contamos ela
	// e depois vamos para subarvore da direita.
	// Aqui percebemos explicitamente que percorremos a árovre in-ordem.
	// Podemos alterar o método percorre-la e não vai influenciar na contagem,
	// mas se percorrermos para a impressão dos dados da árvore, por exemplo,
	// cada modo de percorrer produzirá um resultado diferente.
	return totalDeNos(raiz->esq) + 1 + totalDeNos(raiz->dir);
	
}

// Nessa exibição usamos a notação onde usamos parenteses para agrupar as árvores e suas 
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
