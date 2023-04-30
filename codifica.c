#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lista.h"
#include "codifica.h"

void codifica_msg(chave_t *ch, char *msg_original_name, char *arq_saida_name){
    char c;
    FILE *msg_codificada = fopen(arq_saida_name, "w");
    if (msg_codificada == NULL){
        fprintf(stderr, "[ERRO](modulo %s): Nao foi possivel abrir o arquivo de saida da mensagem a ser codififcada\n", __FILE__);
        exit(1);
    }

    FILE *msg_original = fopen(msg_original_name, "r");
    if (msg_original == NULL){
        fprintf(stderr, "[ERRO](modulo %s): Nao foi possivel abrir o arquivo da menssagem original\n", __FILE__);
        fclose(msg_codificada);
        exit(1);
    }

    while ((c = fgetc(msg_original)) != EOF){
        // para caracteres especiais usar codificar com numeros negativos
        if (c == ' ')
            fprintf(msg_codificada, "%d ", SPACE);
        else if (c == '\n')
            fprintf(msg_codificada, "%d ", NEW_LINE);
        else{
            chave_t *chave = get_chave(ch, tolower(c));
            // Caso a chave nao exista
            if (chave == NULL)
                fprintf(msg_codificada, "%d ", NOT_FOUND);
            else{
                lista_n_t *valor = lista_get(chave, rand() % chave->size);
                // Caso o index nao seja valido,
                // houve algum erro pois empre devia ser
                if (valor == NULL){
                    fprintf(stderr, "[ERRO](modulo %s): Houve algum erro ao pegar valor na chave de caractere [%c]\n", __FILE__, c);
                    exit(1);
                }
                // Coloca o valor do index aleatorio
                fprintf(msg_codificada, "%d ", valor->value);
            }
        }
    }

    fclose(msg_codificada);
    fclose(msg_original);
}
