typedef struct NO* ArvAVL;

ArvAVL* cria_ArvAVL();

void Arvore_AVL(ArvAVL* Raiz);

int ArvAVL_Vazia(ArvAVL* Raiz);

int Altura_ArvAVL(ArvAVL *Raiz);

int Num_Nos(ArvAVL* Raiz);

int Alt_NO(struct NO* no);

int fatorBalaceamento_NO(struct NO* no);

int maior(int x, int y);

int insere_ArvAVL(ArvAVL *Raiz, int valor, char c);

void pre_ordem(ArvAVL *raiz);

void em_ordem(ArvAVL *raiz);

void pos_ordem(ArvAVL *raiz);