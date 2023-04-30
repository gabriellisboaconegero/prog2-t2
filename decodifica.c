#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lista.h"
#include "decodifica.h"

void decodifica_msg(chave_t *chaves,
                    char *msg_codi_name,
                    char *msg_decodi_name){
    int valor = 0;
    chave_t *aux;
    lista_n_t *valor_achado;
    FILE *msg_decodificada = fopen(msg_decodi_name, "w");
    if (msg_decodificada == NULL){
        fprintf(stderr, "[ERRO](modulo %s): Nao foi possivel abrir o arquivo de saida da mensagem a ser decodififcada\n", __FILE__);
        exit(1);
    }

    FILE *msg_codificada = fopen(msg_codi_name, "r");
    if (msg_codificada == NULL){
        fprintf(stderr, "[ERRO](modulo %s): Nao foi possivel abrir o arquivo de MensagemCodificada\n", __FILE__);
        fclose(msg_decodificada);
        exit(1);
    }

    while ((fscanf(msg_codificada, "%d", &valor)) >= 1){
        // Caso seja algum caracter especial, ou nao tenha caracter representante 
        if (valor == SPACE)
            fprintf(msg_decodificada, " ");
        else if (valor == NEW_LINE)
            fprintf(msg_decodificada, "\n");
        else if (valor == NOT_FOUND)
            fprintf(msg_decodificada, "?");
        else{
            valor_achado = NULL;
            aux = chaves;
            // Itera pela lista de chaves e verifica se o valor esta na lista
            // de numeros
            while ((aux != NULL) && (valor_achado == NULL)){
                valor_achado = lista_find(aux->head, valor);
                if (valor_achado == NULL)
                    aux = aux->prox;
            }

            // caso o valor n tenha sido achado
            if (aux == NULL)
                fprintf(msg_decodificada, "?");
            else
                fprintf(msg_decodificada, "%c", aux->ch);
        }
    }

    fclose(msg_decodificada);
    fclose(msg_codificada);
}
