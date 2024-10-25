#include <stdio.h>
#include <stdlib.h>
#include "../include/parser.h"

int main(){
    GHashTable* artist_table = createArtistTable();
    GHashTable* music_table = createMusicTable();
    errosDir();
    parse_artist("dataset", artist_table);
    parse_music("dataset", music_table);
    //parse_user("dataset");
    return 0;
}