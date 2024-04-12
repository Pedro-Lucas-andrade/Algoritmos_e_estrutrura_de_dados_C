#include <stdio.h>
#include <stdlib.h>
#include "arvoreAVL.h"

#define MAX_ARV 150



int main() {
    char k[] = "nos.txt";
    FILE *mensagem;
    FILE *nos;
    
    typedef struct Id_Imp{
        int ids[150];
        int Imp[150];
    } Id_Imp;
    
    int id;
    int ordemDeImpressao;
    char caractere;
    int chave;
    int res;
    Id_Imp idp;
    int qtd = 0, j = 0, l = 0;
    
    ArvAVL *arvore[MAX_ARV];
    
    mensagem = fopen("mensagem.txt", "r");
    nos = fopen(k, "r");
    
    
    void imprime_mensagem(ArvAVL *arvores, int ordem, int id){
        printf("Árvore %d (Ordem %d): \n", id, ordem);
        switch (ordem) {
            case 1:
                pre_ordem(arvores);
                break;
            case 2:
                em_ordem(arvores);
                break;
            case 3:
                pos_ordem(arvores);
                break;
            default:
                printf("Tipo de impressão inválido!\n");
                break;
        }
        printf("\n");
    }
    
    
    if (mensagem == NULL) {
        printf("Erro ao abrir o arquivo mensagem.txt!\n");
        system("pause");
        exit(1);
    } else {
        while (fscanf(mensagem, "%d,%d", &id, &ordemDeImpressao) == 2) {
            arvore[id] = cria_ArvAVL();
            if(arvore[id] != NULL){
                printf("arvore[%d] criada!\n", id);
                qtd++;
                idp.ids[j] = id;
                idp.Imp[j++] = ordemDeImpressao;
            }
        }
        printf("Fim da leitura do arquivo mensagem.txt\n");
    }

    if (nos == NULL) {
        printf("Erro ao abrir o arquivo nos.txt!\n");
        system("pause");
        exit(1);
    } else{
        printf("Iniciando leitura do arquivo nos.txt\n");
        while(fscanf(nos, "%d,%c,%d", &id, &caractere, &chave) != EOF){
            printf("Lido: (%d,%c,%d)\n", id, caractere, chave);
            if(insere_ArvAVL(arvore[id], chave, caractere)){
                printf("Nó: (%d,%c,%d) inserido!\n", id, caractere, chave);
            }
        }
        printf("Fim da leitura do arquivo nos.txt\n");
    }
    
    while( l < qtd){
        imprime_mensagem(arvore[idp.ids[l]], idp.Imp[l], idp.ids[l]);
        l++;
    }
    
    for (int i = 0; i < qtd; i++) {
        Arvore_AVL(arvore[idp.ids[i]]);
    }
    
    fclose(mensagem);
    fclose(nos);
    
    return 0;
}
