#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "lista.h"
#include "lista_chave.h"

chave_t *gera_lista_livro(char *livro_c_name, chave_t *chave_head){
    int j = 0;
    char c;
    chave_t *chave;
    FILE *livro_cifra = fopen(livro_c_name, "r");
    if (livro_cifra == NULL){
        fprintf(stderr, "[ERRO](modulo %s): Nao foi possivel abrir o arquivo [%s]\n",
                __FILE__, livro_c_name);
        exit(1);
    }

    char *palavra = malloc(sizeof(char) * MAX_WORD_SZ);
    if (palavra == NULL){
        fprintf(stderr, "[ERRO](modulo %s): Erro ao alocar memoria\n", __FILE__);
        exit(1);
    }
    // Itera pegando palavra por palavra ate o final do arquivo
    while (fscanf(livro_cifra, "%s", palavra) != EOF){
        c = tolower(palavra[0]);
        // Intervalo de caracteres ascii visiveis
        if (c >= ' ' && c <= '~'){
            chave = insere_chave(&chave_head, tolower(palavra[0]));
            if (insere_lista(chave, j) == NULL){
                fprintf(stderr, "[ERRO](modulo %s): Erro ao inserir valor na lista\n", __FILE__);
                exit(1);
            }
            j++;
        }
    }
    free(palavra);
    fclose(livro_cifra);

    return chave_head;
}

chave_t *gera_lista_arq_chaves(chave_t *chave_head, char *arq_chaves_name){
    int num;
    char chave_c;
    chave_t *chave;
    char *buffer = malloc(sizeof(char) * MAX_ID_SZ);
    if (buffer == NULL){
        fprintf(stderr, "[ERRO](modulo %s): Erro ao alocar memoria\n", __FILE__);
        exit(1);
    }

    FILE *arq_chaves = fopen(arq_chaves_name, "r");
    if (arq_chaves == NULL){
        fprintf(stderr, "[ERRO](modulo %s): Nao foi possivel abrir o arquivo de chaves\n",
                __FILE__);
        exit(1);
    }

    // Primeira chave
    fscanf(arq_chaves, "%s", buffer);
    while (!feof(arq_chaves)){
        // Pega o caracter da chave
        chave_c = buffer[0];
        // Cria chave e comeca a pegar os numeors ate achar uma
        // nova chave no arquivo
        chave = insere_chave(&chave_head, chave_c);
        // Vai pegando letras ate achar algo da forma "%c:", isso quer
        // dizer um novo inicio de chave. Entao atualizar a nova chave,
        // inserindo ela na lista de lista
        while (fscanf(arq_chaves, "%s", buffer) &&
               buffer[1] != ':' &&
               !feof(arq_chaves))
        {
            sscanf(buffer, "%d", &num);
            if (insere_lista_fim(chave, num) == NULL){
                fprintf(stderr, "[ERRO](modulo %s): Erro ao inserir valor na lista\n", __FILE__);
                exit(1);
            }
        }
    }

    free(buffer);
    fclose(arq_chaves);

    return chave_head;
}

void gera_arquivo_chaves(chave_t *ch, char *arq_chaves_name){
    FILE *arq_chaves = fopen(arq_chaves_name, "w");
    if (arq_chaves == NULL){
        fprintf(stderr, "[ERRO](modulo %s): Nao foi possivel criar o arquivo de chaves\n",
                __FILE__);
        exit(1);
    }

    while (ch != NULL){
        fprintf(arq_chaves, "%c: ", ch->ch);
        print_lista(ch->head, arq_chaves);
        ch = ch->prox;
    }
    fclose(arq_chaves);
}

