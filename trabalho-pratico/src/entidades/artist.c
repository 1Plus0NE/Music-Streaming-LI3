#include "../../include/entidades/artist.h"

struct artist {
    long int id;
    char* name;
    float recipe_per_stream;
    long int* id_constituent;
    int num_constituent;
    char* country;
    ArtistType type;
};

struct artist_data{
    long int artist_id;
    int total_reproduction;
};

// Função para criar uma estrutura da entidade artista parametrizada.
Artist* createArtist(long int id, char* name, float recipe_per_stream, long int* id_constituent, int num_constituent, char* country, ArtistType type) {
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

    artist -> recipe_per_stream = recipe_per_stream;

    artist -> id_constituent = malloc(num_constituent * sizeof(long int));
    if (!artist -> id_constituent) {
        perror("Erro ao alocar memória para a lista de constituintes.\n");
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
        free(artist -> name);
        free(artist);
        exit(EXIT_FAILURE);
    }
    strcpy(artist -> country, country);

    artist -> type = type;

    return artist;
}

// Função para criar uma estrutura da entidade artista_data parametrizada.
ArtistData* createArtistData(long int artist_id, int total_reproduction) {
    ArtistData* artist_data = (ArtistData*)malloc(sizeof(ArtistData));
    if (!artist_data) {
        perror("Erro ao alocar memória para a estrutura de dados do artista.\n");
        exit(EXIT_FAILURE);
    }

    artist_data -> artist_id = artist_id;
    artist_data -> total_reproduction = total_reproduction;

    return artist_data;
}

//função que passa uma string do tipo do artista para o enum type
ArtistType stringToArtistType(char* type_str){
    if(!type_str){
        fprintf(stderr, "Tipo de artista inválido: NULL string.\n");
        exit(EXIT_FAILURE);
    }

    char* normalized_str = strdup(type_str);
    if(!normalized_str){
        perror("Erro ao alocar memória para normalização do tipo de artista.\n");
        exit(EXIT_FAILURE);
    }
    for(char* p = normalized_str; *p; p++){
        *p = tolower(*p);
    }

    ArtistType type;
    if (strcmp(normalized_str, "individual") == 0){
        type = INDIVIDUAL;
    }else if (strcmp(normalized_str, "group") == 0){
        type = GRUPO;
    }else{
        fprintf(stderr, "Tipo de artista inexistente: %s.\n", type_str);
        free(normalized_str);
        exit(EXIT_FAILURE);
    }

    free(normalized_str); // Liberar memória da string normalizada
    return type;
}

// Função para verificar se o tipo de artista é válido.
int isValidArtistType(char* type_str){
    if(!type_str) return 0;

    char* normalized_str = strdup(type_str);
    if(!normalized_str){
        perror("Erro ao alocar memória para normalização do tipo de artista.\n");
        exit(EXIT_FAILURE);
    }
    for(char* p = normalized_str; *p; p++){
        *p = tolower(*p);
    }

    int is_valid = (strcmp(normalized_str, "individual") == 0 || strcmp(normalized_str, "group") == 0);

    free(normalized_str);
    return is_valid;
}

// Função para libertar a memória de uma entidade do tipo artista.
void freeArtist(Artist* artist){
    if(!artist) return;
    free(artist -> country);
    free(artist -> id_constituent);
    free(artist -> name);
    free(artist);
}

// Função para libertar a memória de uma entidade do tipo artista_data.
void freeArtistData(ArtistData* artist_data){
    if(!artist_data) return;
    free(artist_data);
}

// Função para libertar a memória de uma entidade do tipo artista contida numa hash table
void freeArtistInTable(gpointer value){
    Artist* artist = (Artist*)value;
    free(artist -> country);
    free(artist -> id_constituent);
    free(artist -> name);
    free(artist);
}

// getters de artista.
long int getArtistId(Artist* a){
    return a ? a->id : -1;
}

char* getArtistName(Artist* a){
    return a -> name ? strdup(a -> name) : NULL;
}

float getArtistRecipePerStream(Artist* a){
    return a -> recipe_per_stream;
}

long int* getArtistIdConstituent(Artist* a) {
    if (a->num_constituent > 0) {
        // Alocar memória para a cópia dos IDs como `long int`
        long int* cpy = malloc(a->num_constituent * sizeof(long int));
        memcpy(cpy, a->id_constituent, a->num_constituent * sizeof(long int)); // Copiar corretamente como `long int`
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

ArtistType getArtistType(Artist* a){
    return a -> type;
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

void setArtistType(Artist* a, ArtistType type){
    a -> type = type;
}

long int getArtistIdFromData(ArtistData* a){
    return a ? a -> artist_id : -1;
}

int getArtistTotalReproduction(ArtistData* a){
    return a -> total_reproduction;
}

void setArtistIdFromData(ArtistData* a, long int artist_id){
    a -> artist_id = artist_id;
}

void setArtistTotalReproduction(ArtistData* a, int total_reproduction){
    a -> total_reproduction = total_reproduction;
}

// Função para transformar o enum type em string para impressão nas queries
char* typeToString(ArtistType type){
    switch(type){
        case INDIVIDUAL:{
            char* typeStr = (char*)malloc(11 * sizeof(char));
            strcpy(typeStr, "individual");
            return typeStr;
            }
        case GRUPO:{
            char* typeStr = (char*)malloc(6 * sizeof(char));
            strcpy(typeStr, "group");
            return typeStr;
            }
        default:
        // Em principio nunca acontece
            return NULL;
    }
}