#ifndef GESTOR_MUSIC_H
#define GESTOR_MUSIC_H
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include "../entidades/music.h"
#include <glib.h>

// função para criar uma tabela de músicas.
void createMusicTable();

// função que adiciona uma música á tabela de músicas.
void addMusic(GHashTable* table, Music* music);

// função que remove uma música da tabela de músicas.
void removeMusic(GHashTable* table, int id);

// função que encontra uma música pelo id na tabela.
Music* searchMusic(GHashTable* table, int id);

// função que libera a memória alocada para a tabela de músicas.
void freeMusicTable(GHashTable* table);

#endif