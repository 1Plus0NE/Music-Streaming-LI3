#include "../../include/parser/parser_artist.h"
#define MAX_FILENAME 1024
#define MAX_LINE 2048

// Função que dá parse ao ficheiro de artistas.
void parse_artist(char* path, GestorArtist* gestorArtist){
    parse_csv(path, "artists.csv", gestorArtist, NULL, NULL, process_artist_line, 1);
}

// função que processa uma linha de artista.
void process_artist_line(char* line, void* gestor, void* aux_dataX, void* aux_dataY){
    (void)aux_dataX;
    (void)aux_dataY;
    GestorArtist* gestorArtist = (GestorArtist*)gestor;

    char original_line[MAX_LINE];
    strcpy(original_line, line);
    char* tmp_line = line;

    char *id_str, *name, *description, *rps_str, *id_constituent, *country, *type_str;
    long int id;
    float recipe_per_stream;
    long int* id_constituent_converted;
    int num_constituent;
    ArtistType type;

    id_str = remove_aspas(strsep(&tmp_line, ";"));
    if(!id_str || strlen(id_str) == 0){
        writeErrors(original_line, 1);
        return;
    }
    id = strtol(id_str + 1, NULL, 10);
    name = remove_aspas(strsep(&tmp_line, ";"));
    description = remove_aspas(strsep(&tmp_line, ";"));
    rps_str = remove_aspas(strsep(&tmp_line, ";"));
    recipe_per_stream = atof(rps_str);
    free(rps_str);
    id_constituent = remove_aspas(strsep(&tmp_line, ";"));
    country = remove_aspas(strsep(&tmp_line, ";"));
    type_str = remove_aspas(strsep(&tmp_line, "\n"));

    // validações.
    if(!isFormatValid(id_constituent) || !verifyConstituent(type_str, id_constituent) || isValidArtistType(type_str) == 0){
        writeErrors(original_line, 1);
        free(id_str);
        free(name);
        free(description);
        free(id_constituent);
        free(country);
        free(type_str);
        return;
    }

    type = stringToArtistType(type_str);
    id_constituent_converted = convertID(id_constituent, &num_constituent);

    Artist* a = createArtist(id, name, description, recipe_per_stream, id_constituent_converted, num_constituent, country, type);
    addArtist(gestorArtist, a);

    free(id_constituent_converted);
    free(id_str);
    free(name);
    free(description);
    free(id_constituent);
    free(country);
    free(type_str);
}