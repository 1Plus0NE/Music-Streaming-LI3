/**
 * @file queries.h
 * @brief Funções que respondem ás queries.
 */
#ifndef QUERIES_H
#define QUERIES_H
#include <stdio.h>
#include <glib.h>
#include "gestores/gestor_user.h"
#include "gestores/gestor_music.h"
#include "gestores/gestor_artist.h"
#include "gestores/gestor_album.h"
#include "gestores/gestor_history.h"
#include "entidades/artist.h"
#include "entidades/music.h"
#include "entidades/discography.h"
#include "writer.h"
#include <string.h>
#include "entidades/wrapped.h"

/**
 * @brief Função que responde á query 1.
 * 
 * @param id_str String com o ID do artista.
 * @param gestorUser Gestor de utilizadores.
 * @param gestorArtist Gestor de artistas.
 * @param delimiter Delimitador.
 * @param output_file Ficheiro de output.
 */
void query1(char* id_str, GestorUser* gestorUser, GestorArtist* gestorArtist, char delimiter, FILE* output_file);

/**
 * @brief Função que responde á query 2
 * 
 * @param nArtists Número de artistas.
 * @param country País.
 * @param disco Discografia.
 * @param delimiter Delimitador.
 * @param output Ficheiro de output.
 */
void query2(int nArtists, char* country, Discography* disco, char delimiter, FILE* output);

/**
 * @brief Função que responde á query 3
 * 
 * @param ageMin Idade mínima.
 * @param ageMax Idade máxima.
 * @param gestorUser Gestor de utilizadores.
 * @param delimiter Delimitador.
 * @param output Ficheiro de output.
 */
void query3(int ageMin, int ageMax, GestorUser* gestorUser, char delimiter, FILE* output);

/**
 * @brief Função que responde á query 4
 * 
 * @param gestorHistory Gestor de históricos.
 * @param start_week Intervalo da semana onde começa
 * @param end_week Intervalo da semana onde acaba
 * @param delimiter Delimitador.
 * @param output Ficheiro de output.
 */
void query4(GestorHistory* gestorHistory, char* start_week, char* end_week, char delimiter, FILE* output);

/**
 * @brief Função que responde á query 5
 * 
 * @param gestorHistory Gestor de históricos.
 * @param username Nome de utilizador.
 * @param numRecommendations Número de recomendações.
 * @param delimiter Delimitador.
 * @param output Ficheiro de output.
 */
void query5(GestorHistory* gestorHistory, char* username, int numRecommendations, FILE* output);

/**
 * @brief Função que responde á query 6
 * 
 * @param idUser ID/Username de um utilizador.
 * @param year Ano para o recap do utilizador.
 * @param n N artistas mais ouvidos.
 * @param gestorHistory Gestor de históricos.
 * @param gestorMusic Gestor de músicas.
 * @param delimiter Delimitador.
 * @param output Ficheiro de output.
 */
void query6(char* idUser, char* year, char* n, GestorHistory* gestor_history, GestorMusic* gestorMusic, char delimiter, FILE* output);
#endif