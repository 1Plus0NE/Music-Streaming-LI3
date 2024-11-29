#ifndef PARSER_H
#define PARSER_H
#include "../gestores/gestor_artist.h"
#include "../gestores/gestor_music.h"
#include "../gestores/gestor_user.h"
#include "parser_artist.h"
#include "parser_music.h"
#include "parser_user.h"
#include "../utils.h"
#include "../queries.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
typedef void (*EntityProcessor)(char* line, void* gestor, void* aux_data);

// Função principal de parse que chama os módulos de parse individualmente
void parse_all(char* path, GestorArtist* gestorArtist, GestorMusic* gestorMusic, GestorUser* gestorUser);

// função que faz parse de um csv.
void parse_csv(const char* path, const char* filename, void* gestor, void* aux_data, EntityProcessor process_line, int error_code);

// Função para ler e fazer parse das queries
void parse_queries(char* path, GestorUser* gestorUser, GestorMusic* gestorMusic, GestorArtist* gestorArtist, int measure_flag);

#endif