#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lista.h"
#include "codificacao.h"
#include "chave.h"

void codifica_msg(chave_t *ch, char *msg_original_name, char *arq_saida_name){
    char c;
    FILE *msg_codificada = fopen(arq_saida_name, "w");
    if (msg_codificada == NULL){
        fprintf(stderr, "[ERRO]: Nao foi possivel abrir o arquivo de saida da mensagem a ser codififcada\n");
        exit(1);
    }

    FILE *msg_original = fopen(msg_original_name, "r");
    if (msg_original == NULL){
        fprintf(stderr, "[ERRO]: Nao foi possivel abrir o arquivo da menssagem original\n");
        exit(1);
    }

    while ((c = fgetc(msg_original)) != EOF){
        if (c == ' ')
            fprintf(msg_codificada, "-1 ");
        else if (c == '\n')
            fprintf(msg_codificada, "-3 ");
        else{
            chave_t *chave = get_chave(ch, tolower(c));
            if (chave == NULL)
                fprintf(msg_codificada, "-2 ");
            else{
                lista_n_t *valor = lista_get(chave, rand() % chave->size);
                if (valor == NULL){
                    fprintf(stderr, "[ERRO]: Houve algum erro ao pegar valor na chave de caractere [%c]\n", c);
                    exit(1);
                }
                fprintf(msg_codificada, "%d ", valor->value);
            }
        }
    }

    fclose(msg_codificada);
    fclose(msg_original);
}

void decodifica_msg(chave_t *chaves, char *msg_codi_name, char *msg_decodi_name){
    int valor = 0;
    chave_t *aux;
    lista_n_t *valor_achado;
    FILE *msg_decodificada = fopen(msg_decodi_name, "w");
    if (msg_decodificada == NULL){
        fprintf(stderr, "[ERRO]: Nao foi possivel abrir o arquivo de saida da mensagem a ser decodififcada\n");
        exit(1);
    }

    FILE *msg_codificada = fopen(msg_codi_name, "r");
    if (msg_codificada == NULL){
        fprintf(stderr, "[ERRO]: Nao foi possivel abrir o arquivo de MensagemCodificada\n");
        exit(1);
    }

    while ((fscanf(msg_codificada, "%d", &valor)) >= 1){
        if (valor == -1)
            fprintf(msg_decodificada, " ");
        else if (valor == -3)
            fprintf(msg_decodificada, "\n");
        else{
            valor_achado = NULL;
            aux = chaves;
            while ((aux != NULL) && (valor_achado == NULL)){
                valor_achado = lista_find(aux->head, valor);
                if (valor_achado == NULL)
                    aux = aux->prox;
            }

            if (aux == NULL)
                fprintf(msg_decodificada, "?");
            else
                fprintf(msg_decodificada, "%c", aux->ch);
        }
    }

    fclose(msg_codificada);
    fclose(msg_decodificada);
}
