#ifndef CODIFICA_H_
#define CODIFICA_H_
#include "chave.h"
#define SPACE -1
#define NEW_LINE -2
#define NOT_FOUND -3

void codifica_msg(chave_t *ch, char *msg_original_name, char *arq_saida_name);
#endif
