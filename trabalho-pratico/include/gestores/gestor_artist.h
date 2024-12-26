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

// função que adiciona um artista e a sua receita à tabela de receitas.
void addArtistRecipe(GestorArtist* gestorArtist, long int artist_id, float recipe);

// função que atualiza a receita de um artista na tabela de receitas.
void updateArtistRecipe(GestorArtist* gestorArtist, long int artist_id, float recipe);

// função que retorna a receita de um artista na tabela de receitas.
float getArtistRecipe(GestorArtist* gestorArtist, long int artist_id);

// função que remove um artista da tabela de receitas.
void removeArtistRecipe(GestorArtist* gestorArtist, long int artist_id);

// Função para liberar a memória alocada para os artistas na tabela.
void freeArtistRecipeInTable(gpointer key, gpointer value, gpointer user_data);

// função que adiciona um artista e o número de álbuns à tabela de contador de álbuns.
void addIndividualAlbumCount(GestorArtist* gestorArtist, long int artist_id, int count);

// função que atualiza o número de álbuns de um artista na tabela de contador de álbuns.
void updateIndividualAlbumCount(GestorArtist* gestorArtist, long int artist_id, int count);

// função que retorna o número de álbuns de um artista na tabela de contador de álbuns.
int getIndividualAlbumCount(GestorArtist* gestorArtist, long int artist_id);

// função que remove um artista da tabela de contador de álbuns.
void removeIndividualAlbumCount(GestorArtist* gestorArtist, long int artist_id);

// Função para liberar a memória alocada para os artistas na tabela de contador de álbuns.
void freeAlbumCountInTable(gpointer key, gpointer value, gpointer user_data);

// Função que verifica se a chave existe na tabela de artistas.
bool containsArtistID(GestorArtist* gestorArtist, long int id);

// Função que verifica se todos a lista de ids existe na tabela de artistas.
bool validateArtistIDs(GestorArtist* gestorArtist, long int *idList, int N);

// Função que percorre a Hash Table e insere cada artista na lista Discography
Discography* fillWithArtists(GestorArtist* gestorArtist, Discography* disco);

// Função  para cada item da Hash Table
void artistFromTableToLL(G_GNUC_UNUSED gpointer artistId, gpointer artistData, gpointer discoPtr);

#endif