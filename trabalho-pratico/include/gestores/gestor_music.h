#ifndef GESTOR_MUSIC_H
#define GESTOR_MUSIC_H
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include "../entidades/music.h"
#include "../entidades/discography.h"
#include <glib.h>
#include <stdbool.h>

typedef struct gestor_music GestorMusic;

// função para criar uma tabela de músicas.
GestorMusic* createGestorMusic();

// função que adiciona uma música á tabela de músicas.
void addMusic(GestorMusic* gestorMusic, Music* music);

// função que remove uma música da tabela de músicas.
void removeMusic(GestorMusic* gestorMusic, long int id);

// função que encontra uma música pelo id na tabela.
Music* searchMusic(GestorMusic* gestorMusic, long int id);

// função que aplica uma função callback em cada item da tabela de músicas.
void foreachMusic(GestorMusic* gestorMusic, GFunc func, gpointer user_data);

// Função para liberar a memória da tabela de músicas.
void freeGestorMusic(GestorMusic* gestorMusic);

// Função principal para percorrer a hash table e atualizar as durações dos artistas
Discography* updateArtistsDurationFromMusic(GestorMusic* gestorMusic, Discography* disco);

// Função para processar cada música e atualizar a duração nos artistas correspondentes
void artistDurationAdd(G_GNUC_UNUSED gpointer musicId, gpointer musicData, gpointer discoPtr);

// Função que verifica se todos os ids das musicas pertencem à tabela
bool validateMusicId(GestorMusic* gestorMusic, long int* id, int N);

// Função que verifica a existência de uma musica pelo seu id, na tabela de musicas
bool containsMusicID(GestorMusic* gestorMusic, long int id);

#endif