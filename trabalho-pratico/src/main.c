#include <stdio.h>
#include <stdlib.h>
#include "../include/parser.h"
#include "../include/queries.h"
#define OUTPUT_DIR "../resultados"

int main(int argc, char* argv[]){
    if(argc < 2){
        fprintf(stderr, "%s apenas contem o nome do programa e nao as diretorias.\n", argv[0]);
        return EXIT_FAILURE;
    }
    char* dataDir = argv[1];
    char* queriesFile = argc > 2 ? argv[2] : NULL;

    GestorArtist* gestorArtist = createGestorArtist();
    GestorMusic* gestorMusic = createGestorMusic();
    GestorUser* gestorUser = createGestorUser();

    errosDir();
    
    parse_artist(dataDir, gestorArtist);
    printf("parse_artist bem sucedido\n");
    parse_music(dataDir, gestorMusic, gestorArtist);
    printf("parse_music bem sucedido\n");
    parse_user(dataDir, gestorUser, gestorMusic);
    printf("parse_user bem sucedido\n");

    if(queriesFile){
        parse_queries(queriesFile, gestorUser, gestorMusic, gestorArtist);
    }
    printf("Fim Queries\n");

    freeGestorArtist(gestorArtist);
    freeGestorMusic(gestorMusic);
    freeGestorUser(gestorUser);

    return 0;
}