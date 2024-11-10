#include <stdio.h>
#include <stdlib.h>
#include "../include/parser/parser.h"
#include "../include/queries.h"
#define OUTPUT_DIR "../resultados"

int main(int argc, char* argv[]){
    if(argc < 2){
        fprintf(stderr, "%s apenas contém o nome do programa e não as diretorias.\n", argv[0]);
        return EXIT_FAILURE;
    }
    char* dataDir = argv[1];
    char* queriesFile = argc > 2 ? argv[2] : NULL;

    GestorArtist* gestorArtist = createGestorArtist();
    GestorMusic* gestorMusic = createGestorMusic();
    GestorUser* gestorUser = createGestorUser();

    errosDir();
    
    parse_all(dataDir, gestorArtist, gestorMusic, gestorUser);
    printf("parse bem sucedido\n");

    if(queriesFile){
        parse_queries(queriesFile, gestorUser, gestorMusic, gestorArtist, 0);
    }
    printf("Fim Queries\n");

    freeGestorArtist(gestorArtist);
    freeGestorMusic(gestorMusic);
    freeGestorUser(gestorUser);

    return 0;
}