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

    GHashTable* artist_table = createArtistTable();
    GHashTable* music_table = createMusicTable();
    GHashTable* user_table = createUserTable();

    errosDir();

    parse_artist(dataDir, artist_table);
    parse_music(dataDir, music_table, artist_table);
    parse_user(dataDir, user_table, music_table);

    if(queriesFile){
        parse_queries(queriesFile, OUTPUT_DIR, user_table, music_table, artist_table);
    }

    freeArtistTable(artist_table);
    freeMusicTable(music_table);
    freeUserTable(user_table);
    return 0;
}