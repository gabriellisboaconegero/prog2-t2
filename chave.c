#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lista.h"
#include "chave.h"

chave_t *inicia_chave(char c){
    chave_t *chave = malloc(sizeof(chave_t));
    if (chave == NULL)
        return NULL;

    chave->size = 0;
    chave->head = NULL;
    chave->tail = NULL;
    chave->ch = c;
    chave->prox = NULL;

    return chave;
}


chave_t *insere_chave(chave_t **ch, char c){
    chave_t *nova_chave;
    chave_t *aux2;

    if (*ch == NULL){
        *ch = inicia_chave(c);
        return *ch;
    }
    
    // Para o caso de c ser menor que o primeiro valor das chaves
    if ((*ch)->ch > c){
        nova_chave = inicia_chave(c);
        if (nova_chave == NULL){
            fprintf(stderr, "[ERRO](modulo %s): Erro ao alocar memoria\n", __FILE__);
            exit(1);
        }
        nova_chave->prox = (*ch);
        *ch = nova_chave;

        return nova_chave;
    }else if ((*ch)->ch == c)
        return *ch;

    aux2 = (*ch);
    // itera ate achar um maior ou igual, ou chegar no final
    while (aux2->prox != NULL && aux2->prox->ch < c)
        aux2 = aux2->prox;

    // Se chegou no final da lista
    if (aux2->prox == NULL){
        nova_chave = inicia_chave(c);
        aux2->prox = nova_chave;

        return nova_chave;
    }else if (aux2->prox->ch != c){
        nova_chave = inicia_chave(c);
        if (nova_chave == NULL){
            fprintf(stderr, "[ERRO](modulo %s): Erro ao alocar memoria\n", __FILE__);
            exit(1);
        }
        nova_chave->prox = aux2->prox;
        aux2->prox = nova_chave;

        return nova_chave;
    }

    return aux2->prox;
}

chave_t *get_chave(chave_t *ch, char c){
    // itera ate achar uma chave com calor maior ou igual a c
    while (ch != NULL && ch->ch < c)
        ch = ch->prox;

    // Se nao achar ou chegar no final
    if (ch == NULL || ch->ch != c)
        return NULL;

    return ch;
}

chave_t *destroi_chave(chave_t *ch){
    chave_t *aux;

    while (ch != NULL){
        destroi_lista(ch->head);
        aux = ch->prox;
        free(ch);
        ch = aux;
    }

    return (chave_t *)NULL;
}

