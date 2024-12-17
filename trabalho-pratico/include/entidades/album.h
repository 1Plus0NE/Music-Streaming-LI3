#ifndef ALBUM_H
#define ALBUM_H
#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../utils.h"
#include "glib.h"

//forma de enunciar a entidade album.
typedef struct album Album;

// função para criar uma estrutura da entidade álbum parametrizada.
Album* createAlbum(long int id, char* title, long int* artist_ids, int num_artists,  int year, char** producers, int num_producers);

// Função para liberar a memória de uma entidade do tipo álbum.
void freeAlbum(Album* album);

// Função para liberar a memória de um álbum em uma hash table.
gboolean freeAlbumInTable(gpointer key, gpointer value, gpointer user_data);

// getters e setters de álbum.
long int getAlbumId(Album* album);

char* getAlbumTitle(Album* album);

long int* getAlbumArtistIds(Album* album);

int getAlbumNumArtists(Album* album);

int getAlbumYear(Album* album);

char** getAlbumProducers(Album* album);

int getAlbumNumProducers(Album* album);

void setAlbumId(Album* album, long int id);

void setAlbumTitle(Album* album, char* title);

void setAlbumArtistIds(Album* album, long int* artist_ids, int num_artists);

void setAlbumNumArtists(Album* album, int num_artists);

void setAlbumYear(Album* album, int year);

void setAlbumProducers(Album* album, char** producers, int num_producers);

void setAlbumNumProducers(Album* album, int num_producers);

#endif