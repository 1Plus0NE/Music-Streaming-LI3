/**
 * @file utils.h
 * @brief Funções auxiliares.
 */
#ifndef UTILS_H
#define UTILS_H
#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#define _XOPEN_SOURCE 700
#endif
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include "entidades/artist.h"
#include "entidades/user.h"

/**
 * @brief Função que remove as aspas de uma string.
 * @details Função que remove as aspas de uma string.
 * 
 * @param str String.
 * @return Retorna a string sem as aspas.
 */
char* remove_aspas(char* str);

/**
 * @brief Função que remove os espaços de uma string.
 * @details Função que remove os espaços de uma string.
 * 
 * @param input String.
 * @return Retorna a string sem espaços.
 */
char* remove_espacos(char* input);

/**
 * @brief Função que verifica se uma string é um número.
 * @details Função que verifica se uma string é um número.
 * 
 * @param str String.
 * @return Retorna 1 se for um número e 0 caso contrário.
 */
int strDigit(char *str);

/**
 * @brief Função que verifica o nome.
 * @details Função que verifica se o nome é válido.
 * 
 * @param name Nome.
 * @return Retorna 1 se for válido e 0 caso contrário.
 */
int nameVerify(char *name);

/**
 * @brief Função que verifica o email.
 * @details Função que verifica se o email é válido.
 * 
 * @param email Email.
 * @return Retorna 1 se for válido e 0 caso contrário.
 */
int emailVerify(char *email);

/**
 * @brief Função que verifica uma data de nascimento.
 * @details Função que verifica se a data de nascimento é válida.
 * 
 * @param birth_date Data de nascimento.
 * @return Retorna 1 se for válida e 0 caso contrário.
 */
int birthDateVerify(char* birth_date);

/**
 * @brief Função que verifica uma duracao.
 * @details Função que verifica se a duração é válida.
 * 
 * @param duration Duração.
 * @return Retorna 1 se for válida e 0 caso contrário.
 */
int verify_duration(char* duration);

/**
 * @brief Função que verifica um ano.
 * @details Função que verifica se o ano é válido.
 * 
 * @param year Ano.
 * @return Retorna 1 se for válido e 0 caso contrário.
 */
int verify_year(int year);

/**
 * @brief Função que calcula a idade.
 * @details Função que calcula a idade.
 * 
 * @param birthdate Data de nascimento.
 * @return Retorna a idade.
 */
int calculaIdade(char* birthdate);

/**
 * @brief Função que verifica a validade de constituintes.
 * @details Função que verifica se os constituintes são válidos.
 * 
 * @param type Tipo.
 * @param constituent Constituinte.
 * @return Retorna 1 se for válido e 0 caso contrário.
 */
int verifyConstituent(char* type, char* constituent);

/**
 * @brief Função que verifica a validade de um id.
 * 
 * @param input ID.
 * @return Retorna 1 se for válido e 0 caso contrário.
 */
int isFormatValid(const char *input);

/**
 * @brief Função que converte um ID de string para long int.
 * @details Função que converte um ID de string para long int.
 * 
 * @param input ID.
 * @param count Contador.
 * @return Retorna o ID convertido.
 */
long int* convertID(const char *input, int *count);

/**
 * @brief Função que liberta a memória de um array de strings.
 * @details Função que liberta a memória de um array de strings.
 * 
 * @param array Array de strings.
 * @param num_elements Número de elementos.
 */
void freeStringArray(char** array, int num_elements);

/**
 * @brief Função que divide uma string com base num delimitador.
 * @details Função que divide uma string com base num delimitador.
 * 
 * @param str String.
 * @param delimiter Delimitador.
 * @param num_elements Número de elementos.
 * @return Retorna um array de strings.
 */
char** splitString(const char* str, const char* delimiter, int* num_elements);

/**
 * @brief Função que remove os enters de uma string.
 * @details Função que remove os enters de uma string.
 * 
 * @param input String.
 */
void removeEnters(char *input);

/**
 * @brief Função converte segundos para string.
 * @details Função converte segundos para string.
 * 
 * @param totSeconds Segundos.
 * @return Retorna a string.
 */
char* secondsToString(int totSeconds);

/**
 * @brief Função que devolve o index de um género.
 * @details Função que devolve o index de um género.
 * 
 * @param genre Género.
 * @param genre_array Array de géneros.
 * @param genre_count Número de géneros.
 * @return Retorna o index.
 */
int getGenreIndex(char *genre, char **genre_array, int genre_count);

/**
 * @brief Função que ordena os géneros por likes.
 * @details Função que ordena os géneros por likes.
 * 
 * @param genres Array de géneros.
 * @param genre_likes Array de likes.
 * @param genre_count Número de géneros.
 */
void sortGenresByLikes(char* genres[], long int genre_likes[], int genre_count);

/**
 * @brief Função que verifica se uma idade está dentro de um intervalo.
 * @details Função que verifica se uma idade está dentro de um intervalo.
 * 
 * @param age Idade.
 * @param minAge Idade mínima.
 * @param maxAge Idade máxima.
 * @return Retorna 1 se estiver dentro do intervalo e 0 caso contrário.
 */
int isAgeInRange(int age, int minAge, int maxAge);

/**
 * @brief Função que dados novos arrays de generos e likes, atualiza o conteúdo dos arrays originais de generos e likes.
 * @details Função que dados novos arrays de generos e likes, atualiza o conteúdo dos arrays originais de generos e likes.
 * 
 * @param genres Array de géneros.
 * @param likes Array de likes.
 * @param size Tamanho.
 * @param newGenres Novos géneros.
 * @param newLikes Novos likes.
 * @param newSize Novo tamanho.
 */
void updateGenresAndLikes(char*** genres, long int** likes, int* size, char** newGenres, long int* newLikes, int newSize);

/**
 * @brief Função que dado um género atualiza o conteúdo dos arrays originais.
 * @details Função que dado um género atualiza o conteúdo dos arrays originais.
 * 
 * @param genres Array de géneros.
 * @param listened Array de listened.
 * @param size Tamanho.
 * @param newGenre Novo género.
 */
void updateGenresListenedArray(char*** genres, int** listened, int* size, char* newGenre);

/**
 * @brief Função que verifica se todos os generos de um utilizador candidato a ser recomendado estão no array do user que procura recomendações.
 * @details Função que verifica se todos os generos de um utilizador candidato a ser recomendado estão no array do user que procura recomendações.
 * 
 * @param targetGenres Géneros do utilizador alvo.
 * @param targetSize Tamanho dos géneros do utilizador alvo.
 * @param userGenres Géneros do utilizador.
 * @param userSize Tamanho dos géneros do utilizador.
 */
int allGenresMatch(char** targetGenres, int targetSize, char** userGenres, int userSize);

/**
 * @brief Função que calcula o score de similaridade entre um utilizador alvo e um utilizador novo
 * @details Função que calcula o score de similaridade entre um utilizador alvo e um utilizador novo
 * 
 * @param targetGenres Géneros do utilizador alvo.
 * @param targetListened Número de vezes que o utilizador alvo ouviu cada género.
 * @param targetSize Tamanho dos géneros do utilizador alvo.
 * @param newGenres Géneros do utilizador novo.
 * @param newListened Número de vezes que o utilizador novo ouviu cada género.
 * @param newSize Tamanho dos géneros do utilizador novo.
 * @return Retorna o score de similaridade.
 */
int calculateSimilarityScore(char** targetGenres, int* targetListened, int targetSize, char** newGenres, int* newListened, int newSize);

/**
 * @brief Função que converte um inteiro para uma string.
 * @details Função que converte um inteiro para uma string.
 * 
 * @param value Valor.
 * @return Retorna a string.
 */
char* intToString(int value);

/**
 * @brief Função que converte um float para uma string.
 * @details Função que converte um float para uma string.
 * 
 * @param value Valor.
 * @param decimal_places Casas decimais.
 * @return Retorna a string.
 */
char* floatToString(float value, int decimal_places);

/**
 * @brief Função que converte um long int para uma string.
 * @details Função que converte um long int para uma string.
 * 
 * @param value Valor.
 * @return Retorna a string.
 */
char* longToString(long value);

/**
 * @brief Função que converte um array de long int para um array de strings.
 * @details Função que converte um array de long int para um array de strings.
 * 
 * @param array Array de long int.
 * @param size Tamanho.
 * @return Retorna o array de strings.
 */
char** longArrayToStringArray(const long* array, int size);

/**
 * @brief Função que liberta a memória de um array de strings.
 * @details Função que dado um array de strings, liberta a memória de cada string do array.
 * 
 * @param string_array Array de strings.
 * @param size Tamanho.
 */
void freeStringArray(char** string_array, int size);

/**
 * @brief Função que devolve a chave da semana.
 * @details Função que devolve a chave da semana.
 * 
 * @param timestamp Timestamp.
 * @return Retorna a chave da semana.
 */
char* getWeekKey(const char* timestamp);

/**
 * @brief Função que converte a duração no formato "HH:MM:SS" para segundos.
 * @details Função que converte a duração no formato "HH:MM:SS" para segundos.
 * 
 * @param duration Duração.
 * @return Retorna os segundos.
 */
int duration_to_seconds(const char* duration);

/**
 * @brief Função que cria a diretoria "dataset-errors" e respetivos ficheiros com cabeçalhos.
 * @details Função que cria a diretoria "dataset-errors" e respetivos ficheiros com cabeçalhos.
 */
void errosDir();

/**
 * @brief Função que escreve os erros num ficheiro.
 * @details Função que recebe uma linha e escreve no csv de erros.
 * 
 * @param line Linha.
 * @param csvFile Ficheiro csv.
 */
void writeErrors(char* line, int csvFile);

#endif