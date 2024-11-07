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
    GHashTable* music_table = createMusicTable();
    GHashTable* user_table = createUserTable();

    parse_artist(dataDir, gestorArtist);
    errosDir();

    parse_artist(dataDir, artist_table);
    printf("parse_artist bem sucedido\n");
    parse_music(dataDir, music_table, gestorArtist);
    printf("parse_music bem sucedido\n");
    parse_user(dataDir, user_table, music_table);
    printf("parse_user bem sucedido\n");

    if(queriesFile){
        parse_queries(queriesFile, user_table, music_table, gestorArtist);
    }
    printf("Fim Queries\n");

    freeGestorArtist(gestorArtist);
    freeMusicTable(music_table);
    freeUserTable(user_table);

    return 0;
}