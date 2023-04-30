#ifndef CHAVE_H_
#define CHAVE_H_
#define MAX_WORD_SZ 100
#define MAX_ID_SZ 128

typedef struct chave_t{
    int size;
    char ch;
    struct chave_t *prox;
    struct lista_n_t *head;
    struct lista_n_t *tail;
}chave_t;

chave_t *inicia_chave(char c);
chave_t *insere_chave(chave_t **ch, char c);
chave_t *get_chave(chave_t *ch, char c);
chave_t *destroi_chave(chave_t *ch);
#endif
