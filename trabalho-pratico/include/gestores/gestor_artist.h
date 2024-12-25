#ifndef GESTOR_ARTIST_H
#define GESTOR_ARTIST_H
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../entidades/artist.h"
#include "../entidades/discography.h"
#include <glib.h>

//estrutura do gestor de artistas.
typedef struct gestor_artist GestorArtist;

typedef void (*GHFunc)(void *key, void *value, void *user_data);

// função para criar uma tabela de artistas.
GestorArtist* createGestorArtist();

// função que adiciona um artista á tabela de artistas.
void addArtist(GestorArtist* gestorArtist, Artist* artist);

// função que remove um artista da tabela de artistas.
void removeArtist(GestorArtist* gestorArtist, long int id);

// função que encontra um artista pelo id na tabela.
Artist* searchArtist(GestorArtist* gestorArtist, long int id);

// função que aplica uma função callback em cada item da tabela de artistas.
void foreachArtist(GestorArtist* gestorArtist, GHFunc func, gpointer user_data);

// função que libera a memória alocada para a tabela de artistas.
void freeGestorArtist(GestorArtist* gestorArtist);

// Função que verifica se a chave existe na tabela de artistas.
bool containsArtistID(GestorArtist* gestorArtist, long int id);

// Função que verifica se todos a lista de ids existe na tabela de artistas.
bool validateArtistIDs(GestorArtist* gestorArtist, long int *idList, int N);

// Função que percorre a Hash Table e insere cada artista na lista Discography
Discography* fillWithArtists(GestorArtist* gestorArtist, Discography* disco);

// Função  para cada item da Hash Table
void artistFromTableToLL(G_GNUC_UNUSED gpointer artistId, gpointer artistData, gpointer discoPtr);

// Função que retorna um GPtrArray com os coletivos de um artista
GPtrArray* getArtistCollectives(GestorArtist* gestorArtist, long int artist_id);

// Função que retorna o número de constituintes de um coletivo
int getNumConstituents(GestorArtist* gestorArtist, long int artist_id);

#endif