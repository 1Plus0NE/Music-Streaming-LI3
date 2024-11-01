#include <stdio.h>
#include <stdlib.h>
#include "../include/parser.h"
#include "../include/queries.h"

int main(){
    GHashTable* artist_table = createArtistTable();
    GHashTable* music_table = createMusicTable();
    GHashTable* user_table = createUserTable();
    errosDir();
    parse_artist("../dataset/artists.csv", artist_table);
    parse_music("../dataset/musics.csv", music_table, artist_table);
    //parse_user("dataset");
    freeArtistTable(artist_table);
    freeMusicTable(music_table);
    freeUserTable(user_table);
    return 0;
}