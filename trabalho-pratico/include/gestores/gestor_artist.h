#ifndef GESTOR_ARTIST_H
#define GESTOR_ARTIST_H
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include "../entidades/artist.h"
#include <glib.h>

// função para criar uma tabela de artistas.
GHashTable* createArtistTable();

// função que adiciona um artista á tabela de artistas.
void addArtist(GHashTable* table, Artist* artist);

// função que remove um artista da tabela de artistas.
void removeArtist(GHashTable* table, int id);

// função que encontra um artista pelo id na tabela.
Artist* searchArtist(GHashTable* table, int id);

// função que libera a memória alocada para a tabela de artistas.
void freeArtistTable(GHashTable* table);

#endif