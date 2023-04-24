#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

lista_n_t *insere_lista(chave_t *chave, int value){
    lista_n_t *nodo;

    if (chave == NULL)
        return NULL;

    nodo = malloc(sizeof(lista_n_t));

    if (nodo == NULL)
        return NULL;

    if (chave->head == NULL)
        chave->tail = nodo;

    chave->size++;
    nodo->value = value;
    nodo->prox = chave->head;
    chave->head = nodo;

    return nodo;
}

lista_n_t *insere_lista_fim(chave_t *chave, int value){
    lista_n_t *nodo;

    if (chave == NULL)
        return NULL;

    nodo = malloc(sizeof(lista_n_t));

    if (nodo == NULL)
        return NULL;

    chave->size++;
    nodo->value = value;
    nodo->prox = NULL;
    if (chave->head == NULL){
        chave->head = nodo;
        chave->tail = nodo;
        return nodo;
    }

    chave->tail->prox = nodo;
    chave->tail = nodo;


    return nodo;
}
void print_lista(chave_t *chave, FILE *f){
    lista_n_t *aux;

    if (chave == NULL){
        fprintf(f, "[NULL]\n");
        return;
    }

    aux = chave->head;
    while (aux != NULL){
        fprintf(f, "%d ", aux->value);
        aux = aux->prox;
    }
    fprintf(f, "\n");
}

lista_n_t *destroi_lista(lista_n_t *l){
    lista_n_t *aux;

    while (l != NULL){
        aux = l->prox;
        free(l);
        l = aux;
    }

    return (lista_n_t *)NULL;
}


lista_n_t *lista_get(chave_t *chave, int index){
    lista_n_t *aux;

    if (chave == NULL)
        return NULL;

    if (index >= chave->size)
        return NULL;

    aux = chave->head;
    while (index-- > 0)
        aux = aux->prox;

    return aux;
}

lista_n_t *lista_find(lista_n_t *l, int valor){
    while (l != NULL && l->value != valor)
        l = l->prox;

    return l;
}
