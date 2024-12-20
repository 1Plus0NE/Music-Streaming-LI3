#include "../../include/parser/parser_music.h"
#define MAX_FILENAME 1024
#define MAX_LINE 2048

// Função para ler e fazer parse de um ficheiro CSV de músicas.
void parse_music(char* path, GestorMusic* gestorMusic, GestorArtist* gestorArtist){
    // Variaveis para o parse 
    FILE* musics;
    char filename[MAX_FILENAME];
    char line[MAX_LINE];
    char original_line[MAX_LINE];
    char *tmp_line=NULL;

    // Argumentos para a struct de musicas
    char *id_str; // para depois passar para long int
    long int id;
    char* title;
    char* artist_id; // para depois converter para um array de long ints
    long int* artist_id_converted;
    int num_artists;
    //char *album_id_str;
    //long int album_id;
    char* duration;
    char* genre;
    char* year_str;
    int year;
    char* lyrics;

    snprintf(filename,MAX_FILENAME,"%s/musics.csv",path); //abrir ficheiro de musicas

    musics = fopen(filename, "r");
    if(!musics){
        perror("Erro ao abrir o ficheiro csv das musicas.\n");
        exit(EXIT_FAILURE);
    }

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
        free(duration);
        free(genre);
        free(lyrics);

    }
    fclose(musics);
}