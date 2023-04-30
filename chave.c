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
    char buffer[MAX_ID_SZ] = {0};
    chave_t *chave;

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
        print_lista(ch, arq_chaves);
        ch = ch->prox;
    }
    fclose(arq_chaves);
}

