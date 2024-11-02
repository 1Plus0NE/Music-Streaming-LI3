#ifndef PARSER_H
#define PARSER_H
#include "entidades/artist.h"
#include "entidades/music.h"
#include "entidades/user.h"
#include "gestores/gestor_artist.h"
#include "gestores/gestor_music.h"
#include "gestores/gestor_user.h"
#include "utils.h"
#include "queries.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

// Função que cria uma diretoria com os ficheiros de erros, com os headers
void errosDir();

// Função que recebe uma linha e escreve no csv de erros
void writeErrors(char* line, int csvFile);

// Função para ler e fazer parse de um arquivo CSV de artistas.
void parse_artist(char* path, GHashTable* artist_table);

// Função para ler e fazer parse de um ficheiro CSV de músicas.
void parse_music(char* path, GHashTable* music_table, GHashTable* artist_table);

// Função para ler e fazer parse de um arquivo CSV de utilizadores.
void parse_user(char* path, GHashTable* userTable, GHashTable* musicTable);

// Função para ler e fazer parse das queries
void parse_queries(char* path, char* outputDir, GHashTable* userTable, GHashTable* musicTable, GHashTable* artistTable);
#endif