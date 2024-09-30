#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "artist.h"

struct artist {
    int id;
    char* name;
    char* description;
    float recipe_per_stream;
    int* id_constituent;
    int num_constituent;
    char* country;
    char* type;
};

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

// Função para libertar a memória de uma entidade do tipo artista.
void freeArtist(Artist* artist){
    free(artist -> country);
    free(artist -> id_constituent);
    free(artist -> description);
    free(artist -> name);
    free(artist);
}