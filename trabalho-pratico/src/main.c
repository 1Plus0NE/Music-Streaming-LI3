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

    printf("Initializing data structures...\n");
    GestorArtist* gestorArtist = createGestorArtist();
    GestorMusic* gestorMusic = createGestorMusic();
    GestorUser* gestorUser = createGestorUser();
    GestorAlbum* gestorAlbum = createGestorAlbum();
    GestorHistory* gestorHistory = createGestorHistory();

    errosDir();
    printf("Parsing csv files...\n\n");
    parse_all(dataDir, gestorArtist, gestorMusic, gestorUser, gestorAlbum, gestorHistory);

    if(queriesFile){
        printf("\nExecuting queries...\n");
        parse_queries(queriesFile, gestorUser, gestorMusic, gestorArtist, gestorAlbum, gestorHistory, 0);
        printf("Queries executed with success!\n\n");
    }

    printf("Cleaning data structures...\n");
    freeGestorArtist(gestorArtist);
    freeGestorMusic(gestorMusic);
    freeGestorUser(gestorUser);
    freeGestorAlbum(gestorAlbum);
    freeGestorHistory(gestorHistory);

    return 0;
}