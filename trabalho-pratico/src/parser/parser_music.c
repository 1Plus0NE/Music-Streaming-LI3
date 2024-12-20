#include "../../include/parser/parser_music.h"
#define MAX_FILENAME 1024
#define MAX_LINE 2048

// Função que dá parse ao ficheiro de músicas.
void parse_music(char* path, GestorMusic* gestorMusic, GestorArtist* gestorArtist){
    parse_csv(path, "musics.csv", gestorMusic, gestorArtist, process_music_line, 2);
}

// Função para processar uma linha de música.
void process_music_line(char* line, void* gestor, void* aux_data) {
    GestorMusic* gestorMusic = (GestorMusic*)gestor;
    GestorArtist* gestorArtist = (GestorArtist*)aux_data;

    char* tmp_line = line;
    char *id_str, *title, *artist_id, *duration, *genre, *year_str, *lyrics;
    long int id;
    long int* artist_id_converted;
<<<<<<< HEAD
    int num_artists;
    //char *album_id_str;
    //long int album_id;
    char* duration;
    char* genre;
    char* year_str;
    int year;
    char* lyrics;
=======
    int num_artists, year;
>>>>>>> refs/remotes/origin/main

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

<<<<<<< HEAD
    fgets(line, sizeof(line), musics); //skip da primeira linha por ser o header

    while((fgets(line, sizeof(line), musics) != NULL)){
        strcpy(original_line, line);
        tmp_line = line;

        id_str = remove_aspas(strsep(&tmp_line, ";"));
        id = strtol(id_str + 1, NULL, 10);
        title  = remove_aspas(strsep(&tmp_line,";"));
        artist_id  = remove_aspas(strsep(&tmp_line,";"));
        //album_id_str = remove_aspas(strsep(&tmp_line, ";"));
        //album_id = strtol(album_id_str + 1, NULL, 10);
        duration  = remove_aspas(strsep(&tmp_line,";"));
        genre  = remove_aspas(strsep(&tmp_line,";"));
        year_str = (remove_aspas(strsep(&tmp_line,";")));
        year = atoi(year_str);
        free(year_str); // Fazemos free já que não vamos precisar mais 
        lyrics = remove_aspas(strsep(&tmp_line,"\n")); //as lyrics tem o \n lá porque é onde ha mudanca de linha

        if(isFormatValid(artist_id) && verify_year(year) && verify_duration(duration)){
            artist_id_converted = convertID(artist_id, &num_artists); // daqui temos o array de ids de artistas + o num_artists calculado
            if(validateArtistIDs(gestorArtist, artist_id_converted ,num_artists)){
                    Music* m = createMusic(id, title, artist_id_converted, num_artists, duration, genre, year, lyrics); // tirei o album_id 
                    addMusic(gestorMusic, m);
                    free(artist_id_converted);
            }
            else{
                free(artist_id_converted); // fazemos free se ele nao entra no if
                writeErrors(original_line, 2);
            }         
        }
       
        else{
            writeErrors(original_line, 2);
        }   

        free(id_str);
        free(title);
        free(artist_id);
        //free(album_id_str);
=======
    // validações.
    if(!isFormatValid(artist_id) || !verify_year(year) || !verify_duration(duration)){
        writeErrors(line, 2);
        free(title);
        free(artist_id);
>>>>>>> refs/remotes/origin/main
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