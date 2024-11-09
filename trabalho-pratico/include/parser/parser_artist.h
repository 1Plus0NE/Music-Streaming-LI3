#ifndef PARSER_ARTIST_H
#define PARSER_ARTIST_H

#include "../entidades/artist.h"
#include "../gestores/gestor_artist.h"
#include "../utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// função para ler e fazer parse de um ficheiro CSV de artistas.
void parse_artist(char* path, GestorArtist* gestorArtist);

#endif