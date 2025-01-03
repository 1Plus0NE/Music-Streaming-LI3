#include "../../include/parser/parser_album.h"
#define MAX_FILENAME 1024
#define MAX_LINE 2048

// Função que dá parse ao ficheiro de álbuns.
void parse_album(char* path, GestorAlbum* gestorAlbum, GestorArtist* gestorArtist){
    parse_csv(path, "albums.csv", gestorAlbum, gestorArtist, NULL, process_album_line, 4);
}

// Função que processa uma linha de álbum.
void process_album_line(char* line, void* gestor, void* aux_dataX, void* aux_dataY){
    GestorArtist* gestorArtist = (GestorArtist*)aux_dataX;
    (void)aux_dataY;
    GestorAlbum* gestorAlbum = (GestorAlbum*)gestor;

    char original_line[MAX_LINE];
    strcpy(original_line, line);
    char* tmp_line = line;
    
    char *id_str, *title, *artist_ids_str, *year_str, *producers_str;
    long int id;
    long int* artist_ids_converted;
    int num_artists, year;
    char** producers_converted;
    int num_producers;

    id_str = remove_aspas(strsep(&tmp_line, ";"));
    if(!id_str || strlen(id_str) == 0){
        writeErrors(line, 1);
        return;
    }
    id = strtol(id_str + 2, NULL, 10);

    title = remove_aspas(strsep(&tmp_line, ";"));
    artist_ids_str = remove_aspas(strsep(&tmp_line, ";"));
    year_str = remove_aspas(strsep(&tmp_line, ";"));
    producers_str = remove_aspas(strsep(&tmp_line, "\n"));

    //validações.
    if (!isFormatValid(artist_ids_str) || !isFormatValid(producers_str)) {
        writeErrors(original_line, 4);
        free(id_str);
        free(title);
        free(artist_ids_str);
        free(year_str);
        free(producers_str);
        return;
    }

    //conversões.
    artist_ids_converted = convertID(artist_ids_str, &num_artists);
    year = atoi(year_str);
    producers_converted = splitString(producers_str, ",", &num_producers);

    Album* album = createAlbum(id, artist_ids_converted, num_artists, year, producers_converted, num_producers);
    addAlbum(gestorAlbum, album);
    for (int i = 0; i < num_artists; i++) {
        long int artist_id = artist_ids_converted[i];

        // Pega a contagem de álbuns atual para o artista
        int count = getIndividualAlbumCount(gestorArtist, artist_id);

        // Atualiza a contagem de álbuns para o artista
        updateIndividualAlbumCount(gestorArtist, artist_id, count + 1);
    }

    free(artist_ids_converted);
    freeStringArray(producers_converted, num_producers);
    free(id_str);
    free(title);
    free(artist_ids_str);
    free(year_str);
    free(producers_str);
}