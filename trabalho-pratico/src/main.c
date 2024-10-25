#include <stdio.h>
#include <stdlib.h>
#include "../include/parser.h"

int main(){
    GHashTable* artist_table = createArtistTable();
    errosDir();
    parse_artist("dataset", artist_table);
    //parse_musics("dataset");
    //parse_user("dataset");
    return 0;
}