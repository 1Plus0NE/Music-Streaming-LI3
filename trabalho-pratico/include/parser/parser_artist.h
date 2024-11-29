#ifndef PARSER_ARTIST_H
#define PARSER_ARTIST_H

#include "../entidades/artist.h"
#include "../gestores/gestor_artist.h"
#include "../utils.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função que dá parse ao ficheiro de artistas.
void parse_artist(char* path, GestorArtist* gestorArtist);

// Função que processa uma linha do ficheiro de artistas.
void process_artist_line(char* line, void* gestor, void* aux_data);

#endif