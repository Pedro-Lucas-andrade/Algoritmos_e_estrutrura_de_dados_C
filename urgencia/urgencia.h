#define MAX 100

typedef struct fila_de_prioridade FilaPrio;

typedef struct paciente Paciente;

typedef struct hora{
    int hora;
    int minuto;
    int segundo;
} Hora;

struct paciente{
    char nome[30];
    int prioridade;
    Hora hora_de_chegada;
};

FilaPrio* cria_FilaPrio();

void libera_FilaPrio(FilaPrio *fp);

int tamanho_FilaPrio(FilaPrio *fp);

int estaCheia_FilaPrio(FilaPrio *fp);

int estaVazia_FilaPrio(FilaPrio *fp);

int consulta_FilaPrio(FilaPrio *fp, char *nome);

int insere_FilaPrio(FilaPrio *fp, Paciente *Pa);

int remover_FilaPrio(FilaPrio *fp, Paciente *Pa);






