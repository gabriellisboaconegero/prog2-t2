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

FILE *openw_ifn_exist(char *filename);
chave_t *inicia_chave(char c);
chave_t *insere_chave(chave_t **ch, char c);
chave_t *get_chave(chave_t *ch, char c);
chave_t *destroi_chave(chave_t *ch);
chave_t *gera_lista_livro(char *livro_c_name, chave_t *chave_head);
chave_t *gera_lista_arq_chaves(chave_t *chave_head, char *arq_chaves_name);
void gera_arquivo_chaves(chave_t *ch, char *arq_chaves_name);
#endif
