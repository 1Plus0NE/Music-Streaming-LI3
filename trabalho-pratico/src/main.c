#include <stdio.h>
#include <stdlib.h>
#include "../include/parser.h"
#include "../include/queries.h"
#define OUTPUT_DIR "../resultados"

int main(){
    // char* queriesFile = argv[2];
    GHashTable* artist_table = createArtistTable();
    GHashTable* music_table = createMusicTable();
    GHashTable* user_table = createUserTable();
    errosDir();
    parse_artist("../dataset/artists.csv", artist_table);
    parse_music("../dataset/musics.csv", music_table, artist_table);
    parse_user("../dataset/users.csv", user_table, music_table);
    // parse_queries(queriesFile, OUTPUT_DIR, user_table, music_table, artist_table);
    // parse_queries(queriesLocal, OUTPUT_DIR, user_table, music_table, artist_table);
    //parse_user("dataset");
    freeArtistTable(artist_table);
    freeMusicTable(music_table);
    freeUserTable(user_table);
    return 0;
}