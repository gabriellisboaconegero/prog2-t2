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
    
    if ((*ch)->ch > c){
        nova_chave = inicia_chave(c);
        nova_chave->prox = (*ch);
        *ch =  nova_chave;

        return nova_chave;
    }else if ((*ch)->ch == c)
        return *ch;

    aux2 = (*ch);
    while (aux2->prox != NULL && aux2->prox->ch < c)
        aux2 = aux2->prox;

    if (aux2->prox == NULL){
        nova_chave = inicia_chave(c);
        aux2->prox = nova_chave;

        return nova_chave;
    }else if (aux2->prox->ch != c){
        nova_chave = inicia_chave(c);
        nova_chave->prox = aux2->prox;
        aux2->prox = nova_chave;

        return nova_chave;
    }

    return aux2->prox;
}

chave_t *get_chave(chave_t *ch, char c){
    while (ch != NULL && ch->ch != c)
        ch = ch->prox;

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
        fprintf(stderr, "[ERRO]: Nao foi possivel abrir o arquivo [%s]\n", livro_c_name);
        exit(1);
    }

    char *palavra = malloc(sizeof(char) * MAX_WORD_SZ);
    while (fscanf(livro_cifra, "%s", palavra) != EOF){
        c = tolower(palavra[0]);
        if (c >= ' ' && c <= '~'){      // Intervalo de caracteres ascii visiveis
            chave = insere_chave(&chave_head, tolower(palavra[0]));
            insere_lista(chave, j);
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
        fprintf(stderr, "[ERRO]: NAo foi possivel abrir o arquivo de chaves\n");
        exit(1);
    }

    fscanf(arq_chaves, "%s", buffer);
    while (!feof(arq_chaves)){
        chave_c = buffer[0];
        while (fscanf(arq_chaves, "%s", buffer) && buffer[1] != ':' && !feof(arq_chaves)){
            sscanf(buffer, "%d", &num);
            chave = insere_chave(&chave_head, chave_c);                 // quando for um espaco adiciona ele na lista e comeca a pegar o proximo num;
            insere_lista_fim(chave, num);
        }
    }

    fclose(arq_chaves);

    return chave_head;
}

void gera_arquivo_chaves(chave_t *ch, char *arq_chaves_name){
    FILE *arq_chaves = fopen(arq_chaves_name, "w");
    if (arq_chaves == NULL){
        fprintf(stderr, "[ERRO]: Nao foi possivel criar o arquivo de chaves\n");
        exit(1);
    }

    while (ch != NULL){
        fprintf(arq_chaves, "%c: ", ch->ch);
        print_lista(ch, arq_chaves);
        ch = ch->prox;
    }
    fclose(arq_chaves);
}

