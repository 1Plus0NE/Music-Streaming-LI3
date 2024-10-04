#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // utilizada a biblioteca ctype que contem a funcao isdigit que permite verificar se o digito é um numero

// Função que faz a validação sintática da duração de uma música
int verify_musics(char* duration) {
    // se cumpre o formato "hh:mm:ss"
    if (strlen(duration) != 8 && duration[2] != ':' && duration[5] != ':') {
        return 0; // invalid format
    }

    // verificar se as horas, minutos e segundos sao digitos entre 0 e 9
    for (int i = 0; i < 8; i++) {
        if (i != 2 && i != 5) { // nao interessa os ':'
            if (!isdigit(duration[i])) {
                return 0; 
            }
        }
    }

    // convertemos as horas, minutos e segundos a inteiros
    int hours = (duration[0] - '0') * 10 + (duration[1] - '0'); 
    int minutes = (duration[3] - '0') * 10 + (duration[4] - '0');
    int seconds = (duration[6] - '0') * 10 + (duration[7] - '0');

    // verificamos se cumprem os intervalos estabelecidos 
    if (hours < 0 || hours > 100 || minutes < 0 || minutes > 60 || seconds < 0 || seconds > 60) {
        return 0;
    }

    return 1; 
}

// Função responsável por remover as aspas.
char* remove_aspas(char* str){
    if(str[0] == '"' && str[strlen(str) - 1] == '"'){
        str[strlen(str) - 1] = '\0';
        return str + 1;
    }
    return str;
}

// Função para ler e fazer parse de um arquivo CSV de artistas.
int parse_artist_csv(const char* filename) {
    FILE* file = fopen(filename, "r");

    if(!file){
        perror("Erro ao abrir o arquivo csv dos artistas.\n");
        exit(EXIT_FAILURE);
    }

    char line[512];

    fgets(line, sizeof(line), file);

    while(fgets(line, sizeof(line), file)){
        int id;
        char* name = NULL;
        char* description = NULL;
        float recipe_per_stream;
        char* constituents[10]; // dúvida, tamanho de certos arrays e strings
        int num_constituents = 0;
        char* country = NULL;
        char* type = NULL;
        
        char* token = strsep(&line, "\n");
        char* campo;

        for(int i = 0; i <= 8; i++){
            campo = strsep(&token, ";");

            if(campo){
                switch(i){
                    case 0:
                        id = atoi(remove_aspas(campo));
                        break;
                    case 1:
                        name = remove_aspas(campo);
                        break;
                    case 2:
                        description = remove_aspas(campo);
                        break;
                    case 3:
                        recipe_per_stream = atof(remove_aspas(campo));
                        break;
                    case 4:
                        while(campo && num_constituents < 10){
                            constituents[num_constituents++] = remove_aspas(campo);
                            campo = strsep(&token, ";");
                        }
                        break;
                    case 5:
                        country = remove_aspas(campo);
                        break;
                    case 6:
                        type = remove_aspas(campo);
                        break;
                    default:
                        break;
                }
            }
        }
        
        Artist* a = createArtist(id, name, description, recipe_per_stream, constituents, num_constituents, country, type);

        //local onde depois será feita o armazenamento na hashtable(estrutura de dados)

        freeArtist(a);
    }
    fclose(file);
    return 0;
}