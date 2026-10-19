#include <stdio.h>
#include <stdlib.h>

typedef struct No
{
    int valor;
    struct No *esq;
    struct No *dir;
} No;

No *criarNo(int valor)
{
    No *novoNo = (No *)malloc(sizeof(No));
    if (novoNo == NULL)
    {
        printf("Erro de alocacao de memoria.\n");
        return NULL;
    }
    novoNo->valor = valor;
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    return novoNo;
} // zero misterio

struct No *inserir(No *raiz, int valor)
{
    if (raiz == NULL)
    {
        return criarNo(valor);
    }
    // menor que a raiz, vai pra esq
    if (valor < raiz->valor)
    {
        raiz->esq = inserir(raiz->esq, valor);
    }
    ////maior que a raiz, vai pra dir
    else if (valor > raiz->valor)
    {
        raiz->dir = inserir(raiz->dir, valor);
    }
    return raiz;
}

No *buscar(No *raiz, int valor)
{
    if (raiz == NULL || raiz->valor == valor)
    {
        return raiz;
    }
    if (valor < raiz->valor)
    {
        return buscar(raiz->esq, valor);
    }
    else
    {
        return buscar(raiz->dir, valor);
    }
}

void emOrdem(No *raiz)
{
    if (raiz != NULL)
    {
        emOrdem(raiz->esq);
        printf("%d ", raiz->valor);
        emOrdem(raiz->dir);
    }
}

void preOrdem(No *raiz)
{
    if (raiz != NULL)
    {
        printf("%d ", raiz->valor);
        preOrdem(raiz->esq);
        preOrdem(raiz->dir);
    }
}

void posOrdem(No *raiz)
{
    if (raiz != NULL)
    {
        posOrdem(raiz->esq);
        posOrdem(raiz->dir);
        printf("%d ", raiz->valor);
    }
}

No *encontrarMenor(No *raiz)
{
    if (raiz == NULL)
    {
        return NULL;
    }

    while (raiz->esq != NULL)
    {
        raiz = raiz->esq;
    }

    return raiz;
}

No *remover(No* raiz, int valor){
    if (raiz == NULL)
    {
        return NULL;
    }
    if (valor < raiz->valor) {
        raiz->esq = remover(raiz->esq, valor);
    } else if (valor > raiz->valor) {
        raiz->dir = remover(raiz->dir, valor);
    } else{
        //primeiro caso, que seria se o no a ser removido for o filho
        if (raiz->esq == NULL && raiz->dir == NULL)
        {
            free(raiz);
            return NULL;
        }
        //segundo caso, seria de um so filho 
        if (raiz->esq == NULL)
        {
            No* temp = raiz->dir;
            free(raiz);
            return temp;
        }
        if (raiz->dir == NULL) {
            No *temp = raiz->esq;
            free(raiz);
            return temp;
        }
        //terceiro caso, dois filhos
        No *sucessor = encontrarMenor(raiz->dir);
        raiz->valor = sucessor->valor;
        raiz->dir = remover(raiz->dir, sucessor->valor);
    }
    return raiz;
}

int main()
{
    No *raiz = NULL;

    raiz = inserir(raiz, 10);
    raiz = inserir(raiz, 5);
    raiz = inserir(raiz, 3);
    raiz = inserir(raiz, 7);
    raiz = inserir(raiz, 15);
    raiz = inserir(raiz, 22);

    printf("Percurso em ordem: ");
    emOrdem(raiz);
    printf("\nPercurso em pre ordem: ");
    preOrdem(raiz);
    printf("\nPercurso em pos ordem: ");
    posOrdem(raiz);

    int buscaValor = 7;
    No *resultado = buscar(raiz, buscaValor);
    if (resultado != NULL){
        printf("\nValor %d encontrado na arvore.\n", buscaValor);
    }else{
        printf("\nValor %d nao encontrado.\n", buscaValor);
    }
    
    raiz = remover(raiz, 15);
    printf("\nPercurso em ordem, depois de remover o 15: \n");
    emOrdem(raiz);
    raiz = remover(raiz, 5);
    printf("\nPercurso em ordem, depois de remover o 5: \n");
    emOrdem(raiz);
    raiz = remover(raiz, 10);
    printf("\nPercurso em ordem, depois de remover o 5: \n");
    emOrdem(raiz);
    return 0;
}