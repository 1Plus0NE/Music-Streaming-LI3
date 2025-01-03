#ifndef ARTIST_H
#define ARTIST_H
#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../utils.h"
#include "glib.h"

//forma de enunciar a entidade artista.
typedef struct artist Artist;

//enum que representa o atributo tipo de artista.
typedef enum {
    INDIVIDUAL,
    GRUPO
} ArtistType;

// Função para criar uma estrutura da entidade artista parametrizada.
Artist* createArtist(long int id, char* name, float recipe_per_stream, long int* id_constituent, int num_constituent, char* country, ArtistType type);

//função que passa uma string do tipo do artista para o enum type
ArtistType stringToArtistType(char* type_str);

// Função para libertar a memória de uma entidade do tipo artista.
void freeArtist(Artist* artist);

// Função para libertar a memória de uma entidade do tipo artista contida numa hash table
gboolean freeArtistInTable(gpointer key, gpointer value, gpointer user_data);

// getters e setters
long int* getArtistId(Artist* a);

char* getArtistName(Artist* a);

float getArtistRecipePerStream(Artist* a);

long int* getArtistIdConstituent(Artist* a);

int getArtistNumConstituent(Artist* a);

char* getArtistCountry(Artist* a);

ArtistType getArtistType(Artist* a);

void setArtistId(Artist* a, int id);

void setArtistName(Artist* a, char* name);

void setArtistRecipePerStream(Artist* a, float recipe_per_stream);

void setArtistIdConstituent(Artist* a, int* id_constituent, int num_constituent);

void setArtistCountry(Artist* a, char* country);

void setArtistType(Artist* a, ArtistType type);

// Função que passa um tipo de artista para string
char* typeToString(ArtistType type);

// Função que verifica se o tipo de artista é válido
int isValidArtistType(char* type_str);

#endif