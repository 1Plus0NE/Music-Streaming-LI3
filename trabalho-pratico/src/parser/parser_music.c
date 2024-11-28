#include "../../include/parser/parser_music.h"
#define MAX_FILENAME 1024
#define MAX_LINE 2048

// Função para processar uma linha de música.
void process_music_line(char* line, void* gestor, void* aux_data) {
    GestorMusic* gestorMusic = (GestorMusic*)gestor;
    GestorArtist* gestorArtist = (GestorArtist*)aux_data;

    char* tmp_line = line;
    char *id_str, *title, *artist_id, *duration, *genre, *year_str, *lyrics;
    long int id;
    long int* artist_id_converted;
    int num_artists, year;

    id_str = remove_aspas(strsep(&tmp_line, ";"));
    if (!id_str || strlen(id_str) == 0) {
        writeErrors(line, 2);
        return;
    }
    id = strtol(id_str + 1, NULL, 10);
    title = remove_aspas(strsep(&tmp_line, ";"));
    artist_id = remove_aspas(strsep(&tmp_line, ";"));
    duration = remove_aspas(strsep(&tmp_line, ";"));
    genre = remove_aspas(strsep(&tmp_line, ";"));
    year_str = remove_aspas(strsep(&tmp_line, ";"));
    year = atoi(year_str);
    free(year_str);
    lyrics = remove_aspas(strsep(&tmp_line, "\n"));

    // validações.
    if(!isFormatValid(artist_id) || !verify_year(year) || !verify_duration(duration)){
        writeErrors(line, 2);
        free(title);
        free(artist_id);
        free(duration);
        free(genre);
        free(lyrics);
        return;
    }

    artist_id_converted = convertID(artist_id, &num_artists);
    if(!validateArtistIDs(gestorArtist, artist_id_converted, num_artists)){
        free(artist_id_converted);
        writeErrors(line, 2);
        free(title);
        free(artist_id);
        free(duration);
        free(genre);
        free(lyrics);
        return;
    }

    Music* m = createMusic(id, title, artist_id_converted, num_artists, 0, duration, genre, year, lyrics);
    addMusic(gestorMusic, m);

    free(id_str);
    free(artist_id_converted);
    free(title);
    free(artist_id);
    free(duration);
    free(genre);
    free(lyrics);
}