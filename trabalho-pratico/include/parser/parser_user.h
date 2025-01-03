/**
 * @file parser_user.h
 * @brief Ficheiro que contém as funções para fazer parse ao ficheiro de utilizadores.
 */
#ifndef PARSER_USER_H
#define PARSER_USER_H

#include "../gestores/gestor_user.h"
#include "../gestores/gestor_music.h"
#include "../entidades/user.h"
#include "../entidades/music.h"
#include "../utils.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Função de verificação da validade de uma linha de utilizador.
 * 
 * @param line A linha do ficheiro de utilizadores.
 * @param gestorMusic O gestor de músicas.
 * @return int 0 se a linha for válida, 1 se for inválida.
 */
int userLineVerify(char *line, GestorMusic* gestorMusic);

/**
 * @brief Função que faz parse ao ficheiro de utilizadores.
 * @details Função que faz parse ao ficheiro de utilizadores, criando os utilizadores e adicionando-os ao gestor de utilizadores.
 * 
 * @param path O caminho para o ficheiro de utilizadores.
 * @param gestorUser O gestor de utilizadores.
 * @param gestorMusic O gestor de músicas.
 */
void parse_user(char* path, GestorUser* gestorUser, GestorMusic* gestorMusic);

/**
 * @brief Função que processa uma linha do ficheiro de utilizadores.
 * @details Função que processa uma linha do ficheiro de utilizadores de forma específica para utilizadores.
 * 
 * @param line A linha do ficheiro de utilizadores.
 * @param gestor O gestor de utilizadores.
 * @param aux_dataX O gestor de músicas.
 * @param aux_dataY não é utilizado.
 */
void process_user_line(char* line, void* gestor, void* aux_dataX, void* aux_dataY);

#endif