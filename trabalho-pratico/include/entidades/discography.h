#ifndef DISCOGRAPHY_H
#define DISCOGRAPHY_H
#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../utils.h"
#include "glib.h"

//estrutura da discografia
typedef struct discography Discography;

// Função para ordenar a discografia por durações
void sortByDuration(Discography** head);

// Função para incrementar em segundos, a duração da discografia de um artista
void durationAdd(Discography* disco, const char* duration, long int id);

//função para libertar a memória da estrutura discografia.
void freeDiscography(Discography* disco);

// Função que adiciona artista por artista numa lista ligada, ignorando a ordem 
void artistInsert(Discography** disco, long int id, const char* name, const char* country, ArtistType type);

//getters e setters da discografia.
long int* getDiscographyId(Discography* d);

char* getDiscographyName(Discography* d);

char* getDiscographyCountry(Discography* d);

int getDiscographyDuration(Discography* d);

ArtistType getDiscographyType(Discography* d);

Discography* getDiscographyNext(Discography* d);

void setDiscographyId(Discography* d, long int id);

void setDiscographyName(Discography* d, char* name);

void setDiscographyCountry(Discography* d, char* country);

void setDiscographyDuration(Discography* d, int duration);

void setDiscographyType(Discography* d, ArtistType type);

void setDiscographyNext(Discography* d, Discography* next);

#endif