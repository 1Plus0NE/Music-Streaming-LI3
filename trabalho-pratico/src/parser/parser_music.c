#include "../../include/parser/parser_music.h"
#define MAX_FILENAME 1024
#define MAX_LINE 2048

// Função que dá parse ao ficheiro de músicas.
void parse_music(char* path, GestorMusic* gestorMusic, GestorArtist* gestorArtist, GestorAlbum* gestorAlbum){
    parse_csv(path, "musics.csv", gestorMusic, gestorArtist, gestorAlbum, process_music_line, 2);
}

// Função para processar uma linha de música.
void process_music_line(char* line, void* gestor, void* aux_data, void* aux_data2){
    GestorMusic* gestorMusic = (GestorMusic*)gestor;
    GestorArtist* gestorArtist = (GestorArtist*)aux_data;
    GestorAlbum* gestorAlbum = (GestorAlbum*)aux_data2;

    char original_line[MAX_LINE];
    strcpy(original_line, line);
    char* tmp_line = line;

    char *id_str, *title, *artist_id, *album_id_str , *duration, *genre, *year_str, *lyrics;
    long int id;
    long int* artist_id_converted;
    long int album_id;
    int num_artists, year;

    id_str = remove_aspas(strsep(&tmp_line, ";"));
    if(!id_str || strlen(id_str) == 0){
        writeErrors(line, 2);
        return;
    }

    id = strtol(id_str + 1, NULL, 10);
    title = remove_aspas(strsep(&tmp_line, ";"));
    artist_id = remove_aspas(strsep(&tmp_line, ";"));
    album_id_str = remove_aspas(strsep(&tmp_line, ";"));
    duration = remove_aspas(strsep(&tmp_line, ";"));
    genre = remove_aspas(strsep(&tmp_line, ";"));
    year_str = remove_aspas(strsep(&tmp_line, ";"));
    year = atoi(year_str);
    free(year_str);
    lyrics = remove_aspas(strsep(&tmp_line, "\n"));

    // validações.
    if(!isFormatValid(artist_id) || !verify_year(year) || isFormatValid(album_id_str) || !verify_duration(duration)){
        writeErrors(original_line, 2);
        free(id_str); 
        free(title);
        free(artist_id);
        free(duration);
        free(genre);
        free(lyrics);
        return;
    }

    artist_id_converted = convertID(artist_id, &num_artists);
    album_id = strtol(album_id_str + 2, NULL, 10);

    if(!validateArtistIDs(gestorArtist, artist_id_converted, num_artists) || !containsAlbumID(gestorAlbum, album_id)){
        free(artist_id_converted);
        writeErrors(original_line, 2);
        free(id_str); 
        free(title);
        free(artist_id);
        free(duration);
        free(genre);
        free(lyrics);
        return;
    }

    Music* m = createMusic(id, title, artist_id_converted, num_artists, album_id, duration, genre, year, lyrics);
    addMusic(gestorMusic, m);

    free(id_str);
    free(artist_id_converted);
    free(title);
    free(artist_id);
    free(duration);
    free(genre);
    free(lyrics);
}