#ifndef LISTA_H_
#define LISTA_H_
#include "chave.h"

typedef struct lista_n_t {
    int value;
    struct lista_n_t *prox;
}lista_n_t;

lista_n_t *insere_lista(chave_t *chave, int value);
lista_n_t *insere_lista_fim(chave_t *chave, int value);
void print_lista(chave_t *chave, FILE *f);
lista_n_t *destroi_lista(lista_n_t *l);
lista_n_t *lista_get(chave_t *chave, int index);
lista_n_t *lista_find(lista_n_t *l, int valor);
#endif
