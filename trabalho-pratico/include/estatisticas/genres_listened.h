#ifndef GENRES_LISTENED_H
#define GENRES_LISTENED_H
#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <glib.h>

typedef struct genres_listened GenresListened;

// CONSTRUCTOR

GenresListened* createGenresListened(char* username, char** genres, int* listened, int size);

// GETTERS

char* getGenresListenedUsername(const GenresListened* genresListened);
char** getGenresListenedArrayGenres(GenresListened* genresListened);
int* getGenresListenedArrayListened(GenresListened* genresListened);
int getGenresListenedArraysSize(const GenresListened* genresListened);
int getGenresListenedSimilarity(const GenresListened* genresListened);

// SETTERS
void setGenresListenedArrayGenres(GenresListened* genresListened, char** newGenres, int newSize);
void setGenresListenedArrayListened(GenresListened* genresListened, int* newListened, int newSize);
void setSimilarityScore(GenresListened* genresListened, int newSimilarityScore);

// FREE

void freeGenresListened(GenresListened* genresListened);

#endif