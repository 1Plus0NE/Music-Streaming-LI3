#ifndef MUSIC_H
#define MUSIC_H
#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include "../utils.h"
#include "glib.h"

// Forma de enunciar a entidade música.
typedef struct music Music;

// Função para criar uma estrutura da entidade música parametrizada.
Music* createMusic(long int id, char* title, long int* artist_id, int num_artists, char* duration, char* genre, int year, char* lyrics);

// GETTERS
long int* getMusicID(Music* m);

char* getMusicTitle(Music* m);

long int* getMusicArtistIDs(Music* m);

int getMusicNumArtists(Music* m);

char* getMusicDuration(Music* m);

char* getMusicGenre(Music* m);

int getMusicYear(Music* m);

char* getMusicLyrics(Music* m);

// SETTERS
void setMusicID(Music* m, int newID);

void setMusicTitle(Music* m, char* newTitle);

void setMusicArtistIDs(Music* m, long int* newArtistID, int newNumArtists);

void setMusicDuration(Music* m, char* newDuration);

void setMusicGenre(Music* m, char* newGenre);

void setMusicYear(Music* m, int newYear);

void setMusicLyrics(Music* m, char* newLyrics);

// Função para libertar a memória de uma entidade do tipo música.
void freeMusic(Music* music);

// Função para libertar a memória de uma entidade do tipo música contida numa hash table
gboolean freeMusicInTable(gpointer key, gpointer value, gpointer user_data);

#endif