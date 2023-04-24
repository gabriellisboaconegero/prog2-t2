#ifndef CODIFICACAO_H_
#define CODIFICACAO_H_
#include "chave.h"

void codifica_msg(chave_t *ch, char *msg_original_name, char *arq_saida_name);
void decodifica_msg(chave_t *chaves, char *msg_codi_name, char *msg_decodi_name);
#endif
