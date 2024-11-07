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

typedef struct discography Discography;

// Função para ordenar a discografia por durações
void sortByDuration(Discography** head);

// Função para incrementar em segundos, a duração da discografia de um artista
void durationAdd(Discography* disco, const char* duration, long int id);

void freeDiscography(Discography* disco);

// Função que adiciona artista por artista numa lista ligada, ignorando a ordem 
void artistInsert(Discography** disco, long int id, const char* name, const char* country, ArtistType type);

#endif