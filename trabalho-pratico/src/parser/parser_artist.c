#include "../../include/parser/parser_artist.h"
#define MAX_FILENAME 1024
#define MAX_LINE 2048

// função para ler e fazer parse de um ficheiro CSV de artistas.
void parse_artist(char* path, GestorArtist* gestorArtist){
    //variáveis para o parse
    FILE* artists;
    char filename[MAX_FILENAME];
    char line[MAX_LINE];
    char original_line[MAX_LINE];
    char *tmp_line=NULL;
    int erros = 0;

    //argumentos para a struct de artistas
    char *id_str;
    long int id;
    char* name;
    char* description;
    char* rps_str;
    float recipe_per_stream;
    char* id_constituent;
    long int* id_constituent_converted;
    int num_constituent;
    char* country;
    char* type_str;
    ArtistType type;

    snprintf(filename,MAX_FILENAME,"%s/artists.csv", path);

    artists = fopen(filename, "r");
    if(!artists){
        perror("Erro ao abrir o ficheiro csv dos artistas.\n");
        exit(EXIT_FAILURE);
    }

    fgets(line, sizeof(line), artists);
    
    while((fgets(line, sizeof(line), artists) != NULL)){
        strcpy(original_line, line);
        tmp_line = line;

        id_str = remove_aspas(strsep(&tmp_line, ";"));
        id = strtol(id_str + 1, NULL, 10);
        name = remove_aspas(strsep(&tmp_line,";"));
        description = remove_aspas(strsep(&tmp_line,";"));
        rps_str = (remove_aspas(strsep(&tmp_line,";")));
        recipe_per_stream = atof(rps_str);
        free(rps_str);
        id_constituent = remove_aspas(strsep(&tmp_line,";"));
        country = remove_aspas(strsep(&tmp_line,";"));
        type_str = remove_aspas(strsep(&tmp_line,"\n"));
        //type = stringToArtistType(type_str); -> quero verificar primeiro se o field é válido

        if(isFormatValid(id_constituent) && verifyConstituent(type_str,id_constituent)){
            type = stringToArtistType(type_str);
            id_constituent_converted = convertID(id_constituent, &num_constituent);
            Artist* a = createArtist(id, name, description, recipe_per_stream, id_constituent_converted, num_constituent, country, type);
            addArtist(gestorArtist,a);
            free(id_constituent_converted);
        }
       
        else{
            erros++;
            writeErrors(original_line, 1);
        }   
        free(id_str);
        free(name);
        free(description);
        free(id_constituent);
        free(country);
        free(type_str);
    }
    printf("Foram encontrados %d erros.\n", erros);
    fclose(artists);
}