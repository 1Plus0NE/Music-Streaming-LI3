#ifndef ARTIST_H
#define ARTIST_H
#include <stdio.h>

// Forma de enunciar a entidade artista.
typedef struct artist Artist;

// Função para criar uma estrutura da entidade artista parametrizada.
Artist* createArtist(int id, char* name, char* description, float recipe_per_stream, int* id_constituent, int num_constituent, char* country, char* type);

// Função para libertar a memória de uma entidade do tipo artista.
void freeArtist(Artist* artist);

#endif