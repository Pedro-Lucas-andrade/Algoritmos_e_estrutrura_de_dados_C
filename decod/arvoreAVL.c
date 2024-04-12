#include <stdio.h>
#include <stdlib.h>
#include "arvoreAVL.h"

struct NO{
    int chave;
    char caractere;
    int alt; // altura do 
    struct NO* esq;
    struct NO* dir;
};

// Função para criar uma árvore AVL e retorna um ponteiro para a árvore
ArvAVL* cria_ArvAVL() {
    ArvAVL* Raiz = (ArvAVL *)malloc(sizeof(ArvAVL));
    if (Raiz != NULL) {
        *Raiz = NULL;
    }
    return Raiz;
}

void pre_ordem(ArvAVL *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        printf("%c\n",(*raiz)->caractere);
        pre_ordem(&((*raiz)->esq));
        pre_ordem(&((*raiz)->dir));
    }
}

void em_ordem(ArvAVL *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        em_ordem(&((*raiz)->esq));
        printf("%d\n",(*raiz)->caractere);
        em_ordem(&((*raiz)->dir));
    }
}

void pos_ordem(ArvAVL *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        pos_ordem(&((*raiz)->esq));
        pos_ordem(&((*raiz)->dir));
        printf("%d\n",(*raiz)->caractere);
    }
}

// Função para liberar a memória de um nó
void libera_No(ArvAVL No) {
    if (No == NULL) return;
    libera_No(No->esq);
    libera_No(No->dir);
    free(No);
    No = NULL;
}

// Função para liberar a memória de uma árvore AVL
void Arvore_AVL(ArvAVL* Raiz) {
    if (Raiz == NULL || *Raiz == NULL) return;
    libera_No(*Raiz);
    free(*Raiz);
    *Raiz = NULL;
}

// Função para verificar se a árvore AVL está vazia
int ArvAVL_Vazia(ArvAVL* Raiz) {
    if (Raiz == NULL || *Raiz == NULL)
        return 1;
    return 0;
}

// Função para calcular a altura de uma árvore AVL
int Altura_ArvAVL(ArvAVL *Raiz) {
    if (ArvAVL_Vazia(Raiz)) return -1;
    
    int hesq = Altura_ArvAVL(&(*Raiz)->esq);
    int hdir = Altura_ArvAVL(&(*Raiz)->dir);
    
    return (hesq > hdir) ? (hesq + 1) : (hdir + 1);
}

// Função para contar o número de nós em uma árvore AVL
int Num_Nos(ArvAVL* Raiz) {
    if (ArvAVL_Vazia(Raiz)) return 0;
    int hesq = Num_Nos(&(*Raiz)->esq);
    int hdir = Num_Nos(&(*Raiz)->dir);
    return (hdir + hesq + 1);
}

// Função para calcular a altura de um nó
int Alt_NO(struct NO* no) {
    if (no == NULL)
        return -1;
    else
        return (no->alt);
}

// Função para calcular o fator de balanceamento de um nó
int fatorBalanceamento_NO(struct NO* no) {
    return labs(Alt_NO(no->esq) - Alt_NO(no->dir));
}

// Função para obter o maior valor entre dois inteiros
int maior(int x, int y) {
    return (x > y) ? x : y;
}

// Função para rotacionar à esquerda
void RotacaoLL(ArvAVL* Raiz) {
    struct NO *no;
    no = (*Raiz)->esq;
    (*Raiz)->esq = no->dir;
    no->dir = *Raiz;
    (*Raiz)->alt = maior(Altura_ArvAVL(&(*Raiz)->esq), Altura_ArvAVL(&(*Raiz)->dir)) + 1;
    no->alt = maior(Altura_ArvAVL(&(*Raiz)->esq), (*Raiz)->alt) + 1;
    *Raiz = no;
}

// Função para rotacionar à direita
void RotacaoRR(ArvAVL *Raiz) {
    struct NO* no;
    no = (*Raiz)->dir;
    (*Raiz)->dir = no->esq;
    no->esq = (*Raiz);
    (*Raiz)->alt = maior(Altura_ArvAVL(&(*Raiz)->esq), Altura_ArvAVL(&(*Raiz)->dir)) + 1;
    no->alt = maior(Altura_ArvAVL(&no->dir), (*Raiz)->alt) + 1;
    *Raiz = no;
}

// Função para rotacionar duplamente à esquerda
void RotacaoLR(ArvAVL *Raiz) {
    RotacaoRR(&(*Raiz)->esq);
    RotacaoLL(Raiz);
}

// Função para rotacionar duplamente à direita
void RotacaoRL(ArvAVL *Raiz) {
    RotacaoLL(&(*Raiz)->dir);
    RotacaoRR(Raiz);
}

// Função para inserir um nó em uma árvore AVL
int insere_ArvAVL(ArvAVL *Raiz, int valor, char c) {
    if (*Raiz == NULL) {
        struct NO *novo;
        novo = (struct NO*)malloc(sizeof(struct NO));
        if (novo == NULL) return 0;
        
        novo->chave = valor;
        novo->caractere = c;
        novo->alt = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *Raiz = novo;
        return 1;
    }
    
    if (valor == (*Raiz)->chave) {
        printf("Valor duplicado!!\n");
        return 0;
    }
    
    struct NO *atual = *Raiz;
    int res;
    
    if (valor < atual->chave) {
        if ((res = insere_ArvAVL(&(atual->esq), valor, c)) == 1) {
            if (fatorBalanceamento_NO(atual) >= 2) {
                if (valor < (*Raiz)->esq->chave)
                    RotacaoLL(Raiz);
                else
                    RotacaoLR(Raiz); 
            }
        }
    } else {
        if ((res = insere_ArvAVL(&(atual->dir), valor, c)) == 1) {
            if (fatorBalanceamento_NO(atual) >= 2) {
                if (valor > (*Raiz)->dir->chave)
                    RotacaoRR(Raiz);
                else
                    RotacaoRL(Raiz);
            }
        }
    }
    atual->alt = maior(Altura_ArvAVL(&atual->esq), Altura_ArvAVL(&atual->dir)) + 1;
    
    return res;
}
