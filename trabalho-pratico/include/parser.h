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

// Função para ler e fazer parse de um arquivo CSV de artistas.
void parse_artist(char* path, GestorArtist* gestorArtist);

// Função para ler e fazer parse de um ficheiro CSV de músicas.
void parse_music(char* path, GestorMusic* gestorMusic, GestorArtist* gestorArtist);

// Função de verificação da validade de um user
int userLineVerify(char *line, GestorMusic* gestorMusic);

// Função para ler e fazer parse de um arquivo CSV de utilizadores.
void parse_user(char* path, GestorUser* gestorUser, GestorMusic* gestorMusic);

// Função para ler e fazer parse das queries
void parse_queries(char* path, GestorUser* gestorUser, GestorMusic* gestorMusic, GestorArtist* gestorArtist);

#endif