#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <getopt.h>
#include "lista.h"
#include "chave.h"
#include "codifica.h"
#include "decodifica.h"
#include "lista_chave.h"

#define USAGE { \
            fprintf(stderr, "Usage: \n");\
            fprintf(stderr, "\t%s -e -b LivroCifra -m MensagemOriginal -o MensagemCodificada -c ArquivoDeChaves\n", argv[0]);\
            fprintf(stderr, "\t%s -d -i MensagemCodificada -c ArquivoDeChaves -o MensagemDecodificada\n", argv[0]);\
            fprintf(stderr, "\t%s -d -i MensagemCodificada -b LivroCifra -o MensagemDecodificada\n", argv[0]);\
            exit(1);}

int file_exist(char *filename){
    FILE *fd = fopen(filename, "r");
    int exist = fd != NULL;
    if (exist)
        fclose(fd);

    return exist;
}

int main(int argc, char **argv){
    int flag_codifica = 0, flag_decodifica = 0;
    char *livro_c_name = NULL, *msg_original_name = NULL,
         *arq_saida_name = NULL, *arq_chaves_name = NULL, *msg_codi_name = NULL;
    int option;
    chave_t *chaves = NULL;

    // Pega as flags e os argumentos delas
    while ((option = getopt(argc, argv, "edb:m:o:c:i:")) != -1){
        switch(option){
            case 'd':
                flag_decodifica = 1; break;
            case 'e':
                flag_codifica = 1; break;
            case 'b':
                livro_c_name = optarg; break;
            case 'm':
                msg_original_name = optarg; break;
            case 'o':
                arq_saida_name = optarg; break;
            case 'c':
                arq_chaves_name = optarg; break;
            case 'i':
                msg_codi_name = optarg; break;
            default:
                USAGE; break;
        }
    }

    // Verificacao se as flags foram passadas corretamentes
    if (!(flag_codifica ^ flag_decodifica)){
        fprintf(stderr, "[ERRO](modulo %s): Verifique se apenas uma das flags (-e ou -d) seja colocada\n", __FILE__);
        USAGE;
    }else if (flag_codifica &&
            (!livro_c_name || !msg_original_name || ! arq_saida_name))
    {
        fprintf(stderr, "[ERRO](modulo %s): Esta faltando argumentos para a codificacao.\n", __FILE__);
        USAGE;
    }else if (flag_decodifica && (!msg_codi_name || !arq_saida_name)){
        fprintf(stderr, "[ERRO](modulo %s): Esta faltando argumentos para a decodificacao\n", __FILE__);
        USAGE;
    }else if (flag_decodifica &&
            !((arq_chaves_name == NULL) ^ (livro_c_name == NULL)))
    {
        fprintf(stderr, "[ERRO](modulo %s): Verifique se apenas um dos parametros (-b ou -c) foi colocado\n", __FILE__);
        USAGE;
    }else if (flag_codifica && file_exist(arq_chaves_name)){    
        // Verificar se o arquivo e existe e não escrever nele apenas se for codificar
        fprintf(stderr, "[ERRO](modulo %s): O arquivo de saida para o arquivo de chaves [%s], ja existe\n", __FILE__,
                arq_chaves_name);
        USAGE;
    }else if (file_exist(arq_saida_name)){
        fprintf(stderr, "[ERRO](modulo %s): O arquivo de saida para a codificaca/decodificao [%s], ja existe\n", __FILE__,
                arq_saida_name);
        USAGE;
    }


    // Caso esteja codificando (flag -e)
    if (flag_codifica){
        // Gerando chaves do livro cifra
        chaves = gera_lista_livro(livro_c_name, chaves);

        // caso tenha a flag -c, gera arquivo de chaves
        if (arq_chaves_name != NULL)
            gera_arquivo_chaves(chaves, arq_chaves_name);

        // codifica a menssagem original
        codifica_msg(chaves, msg_original_name, arq_saida_name);
    }

    // Caso esteja decodificando (flag -d)
    else if (flag_decodifica){
        // Caso seja passado o arquivo de chaves para gerar a lista de chaves
        if (arq_chaves_name)
            chaves = gera_lista_arq_chaves(chaves, arq_chaves_name);

        // Caso seja passado o livro de cifra
        else
            chaves = gera_lista_livro(livro_c_name, chaves);

        decodifica_msg(chaves, msg_codi_name, arq_saida_name);
    }

    // libera memoria alocada para as chaves
    chaves = destroi_chave(chaves);

    return 0;
}
