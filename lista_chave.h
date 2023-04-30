#ifndef LISTA_CHAVE_H_
#define LISTA_CHAVE_H_
#include "chave.h"

chave_t *gera_lista_livro(char *livro_c_name, chave_t *chave_head);
chave_t *gera_lista_arq_chaves(chave_t *chave_head, char *arq_chaves_name);
void gera_arquivo_chaves(chave_t *ch, char *arq_chaves_name);
#endif
