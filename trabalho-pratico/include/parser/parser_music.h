#ifndef PARSER_MUSIC_H
#define PARSER_MUSIC_H

#include "../gestores/gestor_music.h"
#include "../gestores/gestor_artist.h"
#include "../entidades/music.h"
#include "../entidades/artist.h"
#include "../utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para ler e fazer parse de um ficheiro CSV de músicas.
void parse_music(char* path, GestorMusic* gestorMusic, GestorArtist* gestorArtist);

#endif