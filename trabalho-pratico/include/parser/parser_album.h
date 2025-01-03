/**
 * @file parser_album.h
 * @brief Ficheiro que contém as funções para fazer parse ao ficheiro de álbuns.
 */
#ifndef PARSER_ALBUM_H
#define PARSER_ALBUM_H

#include "../entidades/album.h"
#include "../gestores/gestor_album.h"
#include "../utils.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Função que faz parse ao ficheiro de álbuns.
 * @details Função que faz parse ao ficheiro de álbuns, criando os álbuns e adicionando-os ao gestor de álbuns.
 * 
 * @param path O caminho para o ficheiro de álbuns.
 * @param gestorAlbum O gestor de álbuns.
 * @param gestorArtist O gestor de artistas.
 */
void parse_album(char* path, GestorAlbum* gestorAlbum, GestorArtist* gestorArtist);

/**
 * @brief Função que processa uma linha do ficheiro de álbuns.
 * @details Função que processa uma linha do ficheiro de álbuns de forma específica para álbuns.
 * 
 * @param line A linha do ficheiro de álbuns.
 * @param gestor O gestor de álbuns.
 * @param aux_dataX O gestor de artistas.
 * @param aux_dataY não é utilizado.
 */
void process_album_line(char* line, void* gestor, void* aux_dataX, void* aux_dataY);

#endif