#ifndef GESTOR_ALBUM_H
#define GESTOR_ALBUM_H
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../entidades/album.h"
#include <glib.h>

//estrutura do gestor de álbuns.
typedef struct gestor_album GestorAlbum;

typedef void (*GHFunc)(void *key, void *value, void *user_data);

// função para criar uma tabela de álbuns.
GestorAlbum* createGestorAlbum();

// função que adiciona um álbum à tabela de álbuns.
void addAlbum(GestorAlbum* gestorAlbum, Album* album);

// função que remove um álbum da tabela de álbuns.
void removeAlbum(GestorAlbum* gestorAlbum, long int id);

// função que encontra um álbum pelo id na tabela.
Album* searchAlbum(GestorAlbum* gestorAlbum, long int id);

// função que aplica uma função callback em cada item da tabela de álbuns.
void foreachAlbum(GestorAlbum* gestorAlbum, GHFunc func, gpointer user_data);

// função que libera a memória alocada para a tabela de álbuns.
void freeGestorAlbum(GestorAlbum* gestorAlbum);

// Função que verifica se a chave existe na tabela de álbuns.
bool containsAlbumID(GestorAlbum* gestorAlbum, long int id);

// Função que verifica se todos a lista de ids existe na tabela de álbuns.
bool validateAlbumIDs(GestorAlbum* gestorAlbum, long int *idList, int N);

#endif