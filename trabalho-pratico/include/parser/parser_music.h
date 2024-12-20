#ifndef PARSER_MUSIC_H
#define PARSER_MUSIC_H

#include "../gestores/gestor_music.h"
#include "../gestores/gestor_artist.h"
#include "../entidades/music.h"
#include "../entidades/artist.h"
#include "../utils.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função que dá parse ao ficheiro de músicas.
void parse_music(char* path, GestorMusic* gestorMusic, GestorArtist* gestorArtist);

// Função que processa uma linha do ficheiro de músicas.
void process_music_line(char* line, void* gestor, void* aux_data);

#endif