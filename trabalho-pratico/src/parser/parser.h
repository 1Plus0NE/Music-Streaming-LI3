#ifndef PARSER_H
#define PARSER_H
#define _DEFAULT_SOURCE
#include "../entidades/artist.h"
#include "../entidades/music.h"
#include "../entidades/user.h"
#include "../gestores/gestor_music.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

// Função que cria uma diretoria com os ficheiros de erros, com os headers
void errosDir();

// Função que faz a validação de um artista.
int verify_artist(Artist* artist);

// Função para ler e fazer parse de um arquivo CSV de artistas.
int parse_artist_csv(const char* filename);

// Função para ler e fazer parse de um arquivo CSV de músicas.
void parse_musics(char* path);

// Função para ler e fazer parse de um arquivo CSV de utilizadores.
int parse_user_csv(const char* filename);

#endif