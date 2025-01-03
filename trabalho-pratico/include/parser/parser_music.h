/**
 * @file parser_music.h
 * @brief Ficheiro que contém as funções para fazer parse ao ficheiro de músicas.
 */
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

/**
 * @brief Função que faz parse ao ficheiro de músicas.
 * @details Função que faz parse ao ficheiro de músicas, criando as músicas e adicionando-as ao gestor de músicas.
 * 
 * @param path O caminho para o ficheiro de músicas.
 * @param gestorMusic O gestor de músicas.
 * @param gestorArtist O gestor de artistas.
 * @param gestorAlbum O gestor de álbuns.
 */
void parse_music(char* path, GestorMusic* gestorMusic, GestorArtist* gestorArtist, GestorAlbum* gestorAlbum);

/**
 * @brief Função que processa uma linha do ficheiro de músicas.
 * @details Função que processa uma linha do ficheiro de músicas de forma específica para músicas.
 * 
 * @param line A linha do ficheiro de músicas.
 * @param gestor O gestor de músicas.
 * @param aux_dataX O gestor de artistas.
 * @param aux_dataY O gestor de álbuns.
 */
void process_music_line(char* line, void* gestor, void* aux_dataX, void* aux_dataY);

#endif