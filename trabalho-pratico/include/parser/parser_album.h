#ifndef PARSER_ALBUM_H
#define PARSER_ALBUM_H

#include "../entidades/album.h"
#include "../gestores/gestor_album.h"
#include "../utils.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função que dá parse ao ficheiro de álbuns.
void parse_album(char* path, GestorAlbum* gestorAlbum);

// Função que processa uma linha de álbum.
void process_album_line(char* line, void* gestor, void* aux_data);

#endif