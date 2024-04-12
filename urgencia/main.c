#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "urgencia.h"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define RESET   "\033[0m"

void imprimirMenu() {
    printf("___________________________________\n");
    printf("|     Hospital Albert Einstein     |\n");
    printf("+==================================+\n");
    printf("| Escolha uma das opções:          |\n");
    printf("|                                  |\n");
    printf("| 1- Inserir paciente na fila      |\n");
    printf("| 2- Atender paciente              |\n");
    printf("| 3- Encerrar o programa           |\n");
    printf("+==================================+\n");
}

void limparTela() {
    printf("\033[H\033[J");
}

int recebeResultadoMenu(){
    int resul;
    scanf("%d", &resul);
    while( resul > 3 || resul < 0){
        printf(RED "A opção escolhida está inválida!\n" RESET);
        sleep(2);
        imprimirMenu();
        scanf("%d", &resul);
    }
    return resul;
}

void imprimeMenuRisco(){
    printf("___________________________________\n");
    printf("|      Escolha a cor de risco     |\n");
    printf("+=================================+\n");
    printf("| 1- Vermelha                     |\n");
    printf("| 2- Laranja                      |\n");
    printf("| 3- Amarela                      |\n");
    printf("| 4- Verde                        |\n");
    printf("| 5- Azul                         |\n");
    printf("+=================================+\n");
}

int recebeRisco(){
    int risco;
    scanf("%d", &risco);
    while( risco <= 0 || risco > 5){
        printf(RED "A opção escolhida está inválida!\n" RESET);
        sleep(2);
        imprimeMenuRisco();
        scanf("%d", &risco);
    }
    return risco; 
}

void recebeNome(Paciente *pa){
    printf("Nome: ");
    setbuf(stdin, NULL);
    fgets(pa->nome,30,stdin);
}

void recebeHora(Paciente *pa){
    printf("Hora: ");
    scanf("%d", &pa->hora_de_chegada.hora);
    while(pa->hora_de_chegada.hora > 24){
        printf(RED "Hora inválida!\n" RESET);
        printf("Hora: ");
        scanf("%d", &pa->hora_de_chegada.hora);
    }
    printf("Minutos: ");
    scanf("%d", &pa->hora_de_chegada.minuto);
    while(pa->hora_de_chegada.minuto > 60){
        printf(RED "Minutos inválidos!\n" RESET);
        printf("Minutos: ");
        scanf("%d", &pa->hora_de_chegada.minuto);
    }
    printf("Segundos: ");
    scanf("%d", &pa->hora_de_chegada.segundo);
    while(pa->hora_de_chegada.segundo > 60){
        printf(RED "Segundos inválidos!\n" RESET);
        printf("Segundos: ");
        scanf("%d", &pa->hora_de_chegada.segundo);
    }
}

int verificaDados(Paciente *pa){
    int dadosCorretos;
    limparTela();
    printf("+=================================+\n");
    printf("| Nome: %s                        |\n", pa->nome);
    printf("| risco: %d                       |\n", pa->prioridade);
    printf("| Hora: %d:%d:%d                  |\n", pa->hora_de_chegada.hora, pa->hora_de_chegada.minuto, pa->hora_de_chegada.segundo);
    printf("+=================================+\n");
    printf("| Dados estão corretos?           |\n");
    printf("| 1- SIM                          |\n");
    printf("| 1- NÃO                          |\n");
    printf("+=================================+\n");
    scanf("%d", &dadosCorretos);
    return dadosCorretos;
}

void inserirPaciente(FilaPrio *fp){
    
    Paciente *pa = (Paciente *)malloc(sizeof(Paciente));
    
    recebeNome(pa);
    
    imprimeMenuRisco();
    
    switch(recebeRisco()){
        case 1:
            pa->prioridade = 5;
            break;
        case 2: 
            pa->prioridade = 4;
            break;
        case 3:
            pa->prioridade = 3;
            break;
        case 4: 
            pa->prioridade = 2;
            break;
        case 5:
            pa->prioridade = 1;
            break;
    }
    
    recebeHora(pa);
    
    if(verificaDados(pa) == 2){
        printf(RED "Insira o paciente novamente!!!\n" RESET);
        return;
    }
    
    if(insere_FilaPrio(fp, pa)) 
        limparTela();
        printf(GREEN "Paciente inserido com sucesso!\n" RESET);
}

void removerPaciente(FilaPrio *fp){
    int ResulRemover;
    printf("+=================================+\n");
    printf("| Você deseja atender o paciente? |\n");
    printf("| 1- SIM                          |\n");
    printf("| 1- NÃO                          |\n");
    printf("+=================================+\n");
    scanf("%d", &ResulRemover);
    limparTela();
    switch(ResulRemover){
        case 1:
            Paciente *Pa = (Paciente *)malloc(sizeof(Paciente));
            if( Pa == NULL) return;
            if(remover_FilaPrio(fp, Pa)){
                printf(GREEN "O paciente %s foi atendido com sucesso!\n" RESET, Pa->nome );
            }
            else
                printf(RED "Não tem pacientes aguardando atendimento\n" RESET);
            break;
        case 2:
            break;
    }
        
}

void redirecionaMenu(int ResultMenu, FilaPrio *fp){
    switch (ResultMenu){
        case 1:
            limparTela();
            inserirPaciente(fp);
            break;
        case 2: 
            removerPaciente(fp);
            break;
    }
}

int main()
{
    FilaPrio *fp = cria_FilaPrio();
    int ResultMenu = 0;
    while( ResultMenu != 3){
        imprimirMenu();
        ResultMenu = recebeResultadoMenu();
        redirecionaMenu(ResultMenu, fp);
    }
    libera_FilaPrio(fp);
    printf("Encerrando...");
    
    return 0;
}
