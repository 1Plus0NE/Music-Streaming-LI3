#ifndef ARTIST_H
#define ARTIST_H
#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../utils.h"

// Forma de enunciar a entidade artista.
typedef struct artist Artist;

// Função para criar uma estrutura da entidade artista parametrizada.
Artist* createArtist(long int id, char* name, char* description, float recipe_per_stream, long int* id_constituent, int num_constituent, char* country, char* type);

// Função que faz a validação de um artista.
int verify_artist(Artist* artist);

// Função para libertar a memória de uma entidade do tipo artista.
void freeArtist(Artist* artist);

// getters e setters
int* getArtistId(Artist* a);

char* getArtistName(Artist* a);

char* getArtistDescription(Artist* a);

float getArtistRecipePerStream(Artist* a);

int* getArtistIdConstituent(Artist* a);

int getArtistNumConstituent(Artist* a);

char* getArtistCountry(Artist* a);

char* getArtistType(Artist* a);

void setArtistId(Artist* a, int id);

void setArtistName(Artist* a, char* name);

void setArtistDescription(Artist* a, char* description);

void setArtistRecipePerStream(Artist* a, float recipe_per_stream);

void setArtistIdConstituent(Artist* a, int* id_constituent, int num_constituent);

void setArtistCountry(Artist* a, char* country);

void setArtistType(Artist* a, char* type);

#endif