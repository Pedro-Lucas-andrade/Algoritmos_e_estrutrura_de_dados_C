#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "urgencia.h"

struct fila_de_prioridade{
    int qtd;
    Paciente dados[MAX];
};

FilaPrio* cria_FilaPrio(){
    FilaPrio *fp;
    fp = (FilaPrio *)malloc(sizeof(FilaPrio));
    if( fp != NULL)
        fp->qtd = 0;
    return fp;
}

void libera_FilaPrio(FilaPrio *fp){
    free(fp);
}

int tamanho_FilaPrio(FilaPrio *fp){
    if( fp == NULL){
        return -1;
    } else{
        return fp->qtd;
    }
}

int estaCheia_FilaPrio(FilaPrio *fp){
    if( fp == NULL){
        return -1;
    }
    return (fp->qtd == MAX);
}

int estaVazia_FilaPrio(FilaPrio *fp){
    if( fp == NULL)
        return -1;
    return (fp->qtd == 0);
}

int consulta_FilaPrio(FilaPrio *fp, char *nome){
    if( fp == NULL || fp->qtd == 0) return 0;
    strcpy(nome, fp->dados[0].nome);
    return 1;
}


void promoverElemento(FilaPrio *fp, int filho) {
    int pai = (filho - 1) / 2;
    Paciente aux = fp->dados[filho];

    while (filho > 0 && (
        aux.prioridade > fp->dados[pai].prioridade ||
        (aux.prioridade == fp->dados[pai].prioridade &&
        aux.hora_de_chegada.hora < fp->dados[pai].hora_de_chegada.hora) ||
        (aux.prioridade == fp->dados[pai].prioridade &&
        aux.hora_de_chegada.hora == fp->dados[pai].hora_de_chegada.hora &&
        aux.hora_de_chegada.minuto < fp->dados[pai].hora_de_chegada.minuto) ||
        (aux.prioridade == fp->dados[pai].prioridade &&
        aux.hora_de_chegada.hora == fp->dados[pai].hora_de_chegada.hora &&
        aux.hora_de_chegada.minuto == fp->dados[pai].hora_de_chegada.minuto &&
        aux.hora_de_chegada.segundo < fp->dados[pai].hora_de_chegada.segundo)
    )) {
        fp->dados[filho] = fp->dados[pai];
        filho = pai;
        pai = (filho - 1) / 2;
    }

    fp->dados[filho] = aux;
}

int insere_FilaPrio(FilaPrio *fp, Paciente *Pa){
    if( fp == NULL || estaCheia_FilaPrio(fp)) return 0;
    fp->dados[fp->qtd] = *Pa;
    promoverElemento(fp, fp->qtd);
    fp->qtd++;
    return 1;
}

void desce_Heap(FilaPrio *fp, int pai){
    int filho = 2*pai + 1; Paciente aux;
    while(filho < fp->qtd){
        if(filho < fp->qtd-1)
            if( fp->dados[filho].prioridade < fp->dados[filho + 1].prioridade)
                filho++;
        if( fp->dados[pai].prioridade >= fp->dados[filho].prioridade)
            break;
        aux = fp->dados[pai];
        fp->dados[pai] = fp->dados[filho];
        fp->dados[filho] = aux;
        
        pai = filho;
        filho = 2*pai + 1;
    }
}

int remover_FilaPrio(FilaPrio *fp, Paciente *Pa){
    if( fp == NULL || estaVazia_FilaPrio(fp)) return 0;
    
    strcpy(Pa->nome, fp->dados[0].nome);
    fp->qtd--;
    fp->dados[0] = fp->dados[fp->qtd];
    desce_Heap(fp, 0);
    return 1;
}

