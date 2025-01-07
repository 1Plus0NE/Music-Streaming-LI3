#ifndef WRAPPED_H
#define WRAPPED_H

#include <stdio.h>
#include <glib.h>
#include <string.h>
#include "../gestores/gestor_history.h"
#include "../utils.h"
#include "music.h"
#include "history.h"

/**
 * @brief Lista ligada que armazena informações relevantes para a resolução da query 6
 * 
 */
typedef struct artistsTimes ArtistsTimes;

/**
 * @brief Estrutura que armazena informação sobre o resumo anual de um user
 * 
 */
typedef struct wrapped Wrapped;

// ----------------------------------------------------------------INITS E FREES----------------------------------------------------------------

/**
 * @brief Função responsável pela inicialização de uma estrutura Wrapped
 * 
 * @return Apontador de uma estrutura do tipo Wrapped* 
 */
Wrapped* wrappedInit();

/**
 * @brief Estrutura responsável pela libertação de memóriade uma estrutura Wrapped
 * 
 * @param wrap Apontador para a estrutura Wrapped
 */
void freeWrapped(Wrapped* wrap);

// ----------------------------------------------------------------FUNÇÕES----------------------
/**
 * @brief Função que cria uma nova lista ligada com respetivos valores para adicionar ao fim da lista existente
 * 
 * @param idArtist Array com os ids dos artistas
 * @param numArtists Número de artistas
 * @param idMusic Id da musica
 * @param segundos Duração da musica
 * @return Apontador para aestrutura ArtistsTimes
 */
ArtistsTimes* newArtistTime(long int* idArtist, int numArtists, long int idMusic, int segundos);

/**
 * @brief Função que procura uma música na lista de músicas
 * 
 * @param listMus Lista de músicas
 * @param idMusic Id da música a procurar
 */
void procuraMusica(long int* listMus, long int idMusic);

/**
 * @brief Função que verifica se os artistas na lista do histórico são iguais aos artistas na lista do wrap
 * 
 * @param artistaHist Lista de artistas do histórico
 * @param numArtistsHist Número de artistas no histórico
 * @param artistaWrap Lista de artistas do wrap
 * @return 0 se as listas forem iguais, 1 caso contrário
 */
int listArtistasIguais(long int* artistaHist, int numArtistsHist, long int* artistaWrap);

// ----------------------------------------------------------------GETS E SETS----------------------------------------------------------------
/**
 * @brief Função que obtém o ano presente no wrap
 * 
 * @param wrap Apontador para a estrutura Wrapped
 * @return Ano do wrap
 */
char* getWrapAno(Wrapped* wrap);

/**
 * @brief Função que obtém o ID do Utilizador presente no wrap
 * 
 * @param wrap Apontador para a estrutura Wrapped
 * @return ID do Utilizador
 */
long int getWrapUserId(Wrapped* wrap);

/**
 * @brief Função que retorna o array duplo com os albuns e tempo de audição respetivo
 * 
 * @param wrap Apontador para a estrutura Wrapped
 * @return Matriz/Array duplo de inteiros de álbuns
 */
int** getWrapAlbuns(Wrapped* wrap);

/**
 * @brief Função que retorna o array de horas no wrap, preenchido com o tempo de audição
 * 
 * @param wrap Apontador para a estrutura Wrapped
 * @return Array de inteiros de horas
 */
int* getWrapHoras(Wrapped* wrap);

/**
 * @brief Função que retorna o array com os generos do wrap
 * 
 * @param wrap Apontador para a estrutura Wrapped
 * @return Array de inteiros preenchido com o tempo de audição de cada genero
 */
int* getWrapGeneros(Wrapped* wrap);

/**
 * @brief Função que retorna o array duplo/matriz dos dias do wrap preenchido
 * 
 * @param wrap Apontador para a estrutura Wrapped
 * @return Matriz/array duplo de inteiros representando os dias com o tempo de audição
 */
int** getWrapDias(Wrapped* wrap);

/**
 * @brief Função que obtém a lista de artistas do wrap
 * 
 * @param wrap Apontador para a estrutura Wrapped
 * @return Apontador para a estrutura ArtistsTimes
 */
ArtistsTimes* getWrapArtistsTimes(Wrapped* wrap);

/**
 * @brief Função que obtém a lista de IDs dos artistas na estrutura ArtistsTimes na cabeça da lista
 * 
 * @param at Apontador para a lista
 * @return Array dos IDs dos artistas
 */
long int* getArtistTimesArtistId(ArtistsTimes* at);

/**
 * @brief Função que obtém o tempo total de audição de um artista da lista  ArtistsTimes
 * 
 * @param at Apontador para a estrutura ArtistsTimes
 * @return Tempo total de audição do artista da lista à cabeça
 */
int getArtistTimesListTime(ArtistsTimes* at);

/**
 * @brief Função que obtém a lista de músicas na estrutura ArtistsTimes
 * 
 * @param at Apontador para a estrutura ArtistsTimes
 * @return Array dos IDs das músicas de um artista
 */
long int* getArtistTimesListMus(ArtistsTimes* at);

/**
 * @brief Função que obtém o próximo elemento na estrutura ArtistsTimes
 * 
 * @param at Apontador para a estrutura ArtistsTimes
 * @return Apontador para o próximo elemento da estrutura ArtistsTimes
 */
ArtistsTimes* getArtistTimesNext(ArtistsTimes* at);

/**
 * @brief Função que define o ano no wrap
 * 
 * @param wrap Apontador para a estrutura Wrapped
 * @param ano Novo ano a ser definido
 */
void setWrapAno(Wrapped* wrap, char* ano);

/**
 * @brief Função que define o ID do Utilizador no wrap
 * 
 * @param wrap Apontador para a estrutura Wrapped
 * @param userId Novo Id do Utilizador a ser definido
 */
void setWrapUserId(Wrapped* wrap, long int userId);

/**
 * @brief Função que define um novo álbum no wrap e/ou acrescenta o seu tempo de audição
 * 
 * @param wrap Apontador para a estrutura Wrapped
 * @param albumId ID do álbum
 * @param segundos Tempo de audição em segundos
 */
void setWrapAlbum(Wrapped* wrap, long int albumId, int segundos);

/**
 * @brief Função que incrementa uma hora no wrap em segundos
 * 
 * @param wrap Apontador para a estrutura Wrapped
 * @param hora Hora a ser incrementada
 * @param segundos Duração em segundos
 */
void setWrapHoras(Wrapped* wrap, char* hora, int segundos);

/**
 * @brief Função que incrementa o tempo de audição de um genero no wrap
 * 
 * @param wrap Apontador para a estrutura Wrapped
 * @param generos Genero a ser incrementado
 * @param segundos Duração em segundos
 */
void setWrapGeneros(Wrapped* wrap, char* generos, int segundos);

/**
 * @brief Função que incrementa o tempo de audicão de um dia no wrap
 * 
 * @param wrap Apontador para a estrutura Wrapped
 * @param data Dia a ser incrementado
 * @param segundos Duração em segundos
 */
void setWrapDias(Wrapped* wrap, char* data, int segundos);

/**
 * @brief Função que define uma nova lista no final da lista ligada
 * 
 * @param wrap Apontador para a estrutura Wrapped
 * @param idArtist Array com os IDs dos artistas
 * @param numArtists Número de artistas
 * @param idMusic ID da música
 * @param segundos Duração em segundos
 */
void setWrapArtistTime(Wrapped* wrap, long int* idArtist, int numArtists, long int idMusic, int segundos);

/**
 * @brief Função que obtém o tempo total de audição a partir do array de tempos de audição dos generos, generos[][i]
 * @param wrap Apontador para a estrutura Wrapped
 * @param totalGenre Array com apenas os tempos de audição 
 * @return Tempo total de audição de todo o ano
 */
char* getWrapTotalListTime(Wrapped* wrap, char** totalGenre);

/**
 * @brief Função que obtém o total de músicas presentes na lista ligada de todo o wrap
 * 
 * @param wrap Apontador para a estrutura Wrapped
 * @return Total de musicas ouvidas durante o ano
 */
char* getWrapTotalMusics(Wrapped* wrap);

/**
 * @brief Função que obtém o artista mais ouvido
 * 
 * @param wrap Apontador para a estrutura Wrapped
 * @return Artista mais ouvido durante o ano
 */
char* getWrapTotalArtist(Wrapped* wrap);

/**
 * @brief Função que obtém o dia com mais tempo de audição do ano
 * 
 * @param wrap Apontador para a estrutura Wrapped
 * @return Dia mais ouvido durante o ano
 */
char* getWrapTotalDay(Wrapped* wrap);

/**
 * @brief Função que obtém o album com mais tempo de audição do ano
 * 
 * @param wrap Apontador para a estrutura Wrapped
 * @return Album mais ouvido do ano
 */
char* getWrapTotalAlbum(Wrapped* wrap);

/**
 * @brief Função que obtém a hora com mais tempo de audição do ano
 * 
 * @param wrap Apontador para a estrutura Wrapped
 * @return Hora mais ouvida durante o ano
 */
char* getWrapTotalHour(Wrapped* wrap);

// ----------------------------------------------------------------SORT----------------------------------------------------------------
/**
 * @brief Função que ordena o conteúdo do wrap por ordem decrescente de tempo de audição
 * 
 * @param wrap Apontador para a estrutura Wrapped
 */
void sortWrap(Wrapped* wrap);

#endif