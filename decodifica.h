#ifndef DECODIFICA_H_
#define DECODIFICA_H_
#include "chave.h"
#define SPACE -1
#define NEW_LINE -2
#define NOT_FOUND -3

void decodifica_msg(chave_t *chaves, char *msg_codi_name, char *msg_decodi_name);
#endif
