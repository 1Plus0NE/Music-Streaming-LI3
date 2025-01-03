/**
 * @file parser_history.h
 * @brief Ficheiro que contém as funções para fazer parse ao ficheiro de históricos.
 */
#ifndef PARSER_HISTORY_H
#define PARSER_HISTORY_H

#include "../entidades/history.h"
#include "../gestores/gestor_history.h"
#include "../utils.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Função que faz parse ao ficheiro de históricos.
 * @details Função que faz parse ao ficheiro de históricos, criando os históricos e adicionando-os ao gestor de históricos.
 * 
 * @param path O caminho para o ficheiro de históricos.
 * @param gestorHistory O gestor de históricos.
 * @param gestorMusic O gestor de músicas.
 * @param gestorArtist O gestor de artistas.
 */
void parse_history(char* path, GestorHistory* gestorHistory, GestorMusic* gestorMusic, GestorArtist* gestorArtist);

/**
 * @brief Função que processa uma linha do ficheiro de históricos.
 * @details Função que processa uma linha do ficheiro de históricos de forma específica para históricos.
 * 
 * @param line A linha do ficheiro de históricos.
 * @param gestor O gestor de históricos.
 * @param aux_dataX O gestor de músicas.
 * @param aux_dataY O gestor de artistas.
 */
void process_history_line(char* line, void* gestor, void* aux_dataX, void* aux_dataY);

#endif