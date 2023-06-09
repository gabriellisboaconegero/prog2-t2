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
void print_lista(lista_n_t *head, FILE *f){
    if (head  == NULL){
        fprintf(f, "[NULL]\n");
        return;
    }

    while (head != NULL){
        fprintf(f, "%d ", head->value);
        head = head->prox;
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

    // garantir um index valido
    if (index >= chave->size)
        return NULL;

    aux = chave->head;
    // Decrementando ate achar o nodo com valor do index
    for (;index > 0; index--)
        aux = aux->prox;

    return aux;
}

lista_n_t *lista_find(lista_n_t *l, int valor){
    // itera ate achar um nodo com valor menor ou igual ao valor
    while (l != NULL && l->value > valor)
        l = l->prox;

    // Se nao achar ou chegar no final
    if (l == NULL || l->value != valor)
        return NULL;

    return l;
}
