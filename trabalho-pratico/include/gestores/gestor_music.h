#ifndef GESTOR_MUSIC_H
#define GESTOR_MUSIC_H
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include "../entidades/music.h"
#include "../entidades/discography.h"
#include <glib.h>
//#include <stdbool.h>

// função para criar uma tabela de músicas.
GHashTable* createMusicTable();

// função que adiciona uma música á tabela de músicas.
void addMusic(GHashTable* table, Music* music);

// função que remove uma música da tabela de músicas.
void removeMusic(GHashTable* table, long int id);

// função que encontra uma música pelo id na tabela.
Music* searchMusic(GHashTable* table, long int id);

// função que libera a memória alocada para a tabela de músicas.
void freeMusicTable(GHashTable* table);

// Função principal para percorrer a hash table e atualizar as durações dos artistas
Discography* updateArtistsDurationFromMusic(GHashTable* musicTable, Discography* disco);

// Função para processar cada música e atualizar a duração nos artistas correspondentes
void artistDurationAdd(G_GNUC_UNUSED gpointer musicId, gpointer musicData, gpointer discoPtr);

#endif