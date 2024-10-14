#include "artist.h"

typedef struct artist {
    int id;
    char* name;
    char* description;
    float recipe_per_stream;
    int* id_constituent;
    int num_constituent;
    char* country;
    char* type;
} Artist;

// Função para criar uma estrutura da entidade artista parametrizada.
Artist* createArtist(int id, char* name, char* description, float recipe_per_stream, int* id_constituent, int num_constituent, char* country, char* type) {
    Artist* artist = (Artist*)malloc(sizeof(Artist));
    if (!artist) {
        perror("Erro ao alocar memória para o artista.\n");
        exit(EXIT_FAILURE);
    }

    artist -> id = id;

    artist -> name = malloc(strlen(name) + 1);
    if (!artist -> name) {
        perror("Erro ao alocar memória para o nome do artista.\n");
        free(artist);
        exit(EXIT_FAILURE);
    }
    strcpy(artist -> name, name);

    artist -> description = malloc(strlen(description) + 1);
    if (!artist -> description) {
        perror("Erro ao alocar memória para a descrição do artista.\n");
        free(artist -> name);
        free(artist);
        exit(EXIT_FAILURE);
    }
    strcpy(artist -> description, description);

    artist -> recipe_per_stream = recipe_per_stream;

    artist -> id_constituent = malloc(num_constituent * sizeof(int));
    if (!artist -> id_constituent) {
        perror("Erro ao alocar memória para a lista de constituintes.\n");
        free(artist -> description);
        free(artist -> name);
        free(artist);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < num_constituent; i++) {
        artist -> id_constituent[i] = id_constituent[i];
    }

    artist -> num_constituent = num_constituent;

    artist -> country = malloc(strlen(country) + 1);
    if (!artist -> country) {
        perror("Erro ao alocar memória para o país do artista.\n");
        free(artist -> id_constituent);
        free(artist -> description);
        free(artist -> name);
        free(artist);
        exit(EXIT_FAILURE);
    }
    strcpy(artist -> country, country);

    artist -> type = malloc(strlen(type) + 1);
    if (!artist -> type) {
        perror("Erro ao alocar memória para o tipo de artista.\n");
        free(artist -> country);
        free(artist -> id_constituent);
        free(artist -> description);
        free(artist -> name);
        free(artist);
        exit(EXIT_FAILURE);
    }
    strcpy(artist -> type, type);
    return artist;
}

// Função que faz a validação de um artista.
int verifyLineArtist(char* line){
    char* info;
    char* token = line;
    char* id_constituent_check = NULL;

    for(int i = 0; i < 7; i++){
        info = strsep(&token, ";");

        if(info){
            switch(i){
                case 0:
                    if(!remove_aspas(info) || atoi(remove_aspas(info)) <= 0){
                        return 1;
                    }
                    break;
                case 1:
                    if(!remove_aspas(info) || strlen(remove_aspas(info)) == 0){
                        return 1;
                    }
                    break;
                case 2:
                    if(!remove_aspas(info) || strlen(remove_aspas(info)) == 0){
                        return 1;
                    }
                    break;
                case 3:
                    if(atof(remove_aspas(info)) < 0){
                        return 1;
                    }
                    break;
                case 4:
                    if(remove_aspas(info) && strlen(remove_aspas(info)) > 0){
                        id_constituent_check = "grupo";
                    }else{
                        id_constituent_check = "individual";
                    }
                    break;
                case 5:
                    if(!remove_aspas(info) || strlen(remove_aspas(info)) == 0){
                        return 1;
                    }
                    break;
                case 6:
                    if(strcmp(remove_aspas(info), "individual") != 0 && strcmp(remove_aspas(info), "grupo") != 0 && strcmp(remove_aspas(info), id_constituent_check) != 0){
                        return 1;
                    }
                    break;
                default:
                    break;
            }
        }else{
            return 1;
        }
    }
    return 0;
}

// Função para libertar a memória de uma entidade do tipo artista.
void freeArtist(Artist* artist){
    free(artist -> country);
    free(artist -> id_constituent);
    free(artist -> description);
    free(artist -> name);
    free(artist);
}

// getters de artista.
int* getArtistId(Artist* a){
    return a->id ? &a->id : NULL;
}

char* getArtistName(Artist* a){
    return a -> name ? strdup(a -> name) : NULL;
}

char* getArtistDescription(Artist* a){
    return a -> description ? strdup(a -> description) : NULL;
}

float getArtistRecipePerStream(Artist* a){
    return a -> recipe_per_stream;
}

int* getArtistIdConstituent(Artist* a){
    if(a -> num_constituent > 0){
        int* cpy = malloc(a -> num_constituent * sizeof(int));
        memcpy(cpy, a -> id_constituent, a->num_constituent * sizeof(int));
        return cpy;
    }
    return NULL;
}

int getArtistNumConstituent(Artist* a){
    return a -> num_constituent;
}

char* getArtistCountry(Artist* a){
    return a -> country ? strdup(a -> country) : NULL;
}

char* getArtistType(Artist* a){
    return a -> type ? strdup(a -> type) : NULL;
}

// setters de artista.
void setArtistId(Artist* a, int id){
    a -> id = id;
}

void setArtistName(Artist* a, char* name){
    if(a -> name){
        free(a -> name);
    }
    a -> name = strdup(name);
}

void setArtistDescription(Artist* a, char* description){
    if(a -> description){
        free(a -> description);
    }
    a -> description = strdup(description);
}

void setArtistRecipePerStream(Artist* a, float recipe_per_stream){
    a -> recipe_per_stream = recipe_per_stream;
}

void setArtistIdConstituent(Artist* a, int* id_constituent, int num_constituent){
    if(a -> id_constituent){
        free(a -> id_constituent);
    }
    a -> id_constituent = malloc(num_constituent * sizeof(int));
    memcpy(a -> id_constituent, id_constituent, num_constituent * sizeof(int));
    a -> num_constituent = num_constituent;
}

void setArtistCountry(Artist* a, char* country){
    if(a -> country){
        free(a -> country);
    }
    a -> country = strdup(country);
}

void setArtistType(Artist* a, char* type){
    if(a -> type){
        free(a -> type);
    }
    a -> type = strdup(type);
}