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
Music* createMusic(long int id, long int* artist_id, int num_artists, long int album_id, char* duration, char* genre, int year);

// GETTERS
long int* getMusicID(Music* m);

long int* getMusicArtistIDs(Music* m);

int getMusicNumArtists(Music* m);

long int getMusicAlbumId(Music* m);

char* getMusicDuration(Music* m);

char* getMusicGenre(Music* m);

int getMusicYear(Music* m);

// SETTERS
void setMusicID(Music* m, long int newID);

void setMusicArtistIDs(Music* m, long int* newArtistID, int newNumArtists);

void setMusicAlbumId(Music* m, long int newAlbumId);

void setMusicDuration(Music* m, char* newDuration);

void setMusicGenre(Music* m, char* newGenre);

void setMusicYear(Music* m, int newYear);

// Função para libertar a memória de uma entidade do tipo música.
void freeMusic(Music* music);

// Função para libertar a memória de uma entidade do tipo música contida numa hash table
gboolean freeMusicInTable(gpointer key, gpointer value, gpointer user_data);

#endif