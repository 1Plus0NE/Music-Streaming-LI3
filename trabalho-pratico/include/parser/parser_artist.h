/**
 * @file parser_artist.h
 * @brief Ficheiro que contém as funções para fazer parse ao ficheiro de artistas.
 */
#ifndef PARSER_ARTIST_H
#define PARSER_ARTIST_H

#include "../entidades/artist.h"
#include "../gestores/gestor_artist.h"
#include "../utils.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Função que faz parse ao ficheiro de artistas.
 * @details Função que faz parse ao ficheiro de artistas, criando os artistas e adicionando-os ao gestor de artistas.
 * 
 * @param path O caminho para o ficheiro de artistas.
 * @param gestorArtist O gestor de artistas.
 */
void parse_artist(char* path, GestorArtist* gestorArtist);

/**
 * @brief Função que processa uma linha do ficheiro de artistas.
 * @details Função que processa uma linha do ficheiro de artistas de forma específica para artistas.
 * 
 * @param line A linha do ficheiro de artistas.
 * @param gestor O gestor de artistas.
 * @param aux_dataX não é utilizado.
 * @param aux_dataY não é utilizado.
 */
void process_artist_line(char* line, void* gestor, void* aux_dataX, void* aux_dataY);

#endif