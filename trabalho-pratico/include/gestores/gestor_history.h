/**
 * @file gestor_history.h
 * @brief Definição da estrutura do gestor de históricos e das funções que a manipulam.
 */
#ifndef GESTOR_HISTORY_H
#define GESTOR_HISTORY_H
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../entidades/history.h"
#include "../estatisticas/genres_listened.h"
#include <glib.h>

/**
 * @brief Estrutura que armazena a informação dos históricos.
 * 
 */
typedef struct gestor_history GestorHistory;

/**
 * @brief Estrutura que armazena a informação dos artistas.
 * 
 */
typedef struct artist_table ArtistTable;

typedef void (*GHFunc)(void *key, void *value, void *user_data);

typedef bool (*IsMusicByArtistFunc)(long int music_id, long int artist_id);

/**
 * @brief Função que cria uma entidade do tipo gestor de históricos.
 * @details A função aloca memória para a estrutura do gestor de históricos e inicializa a tabela de históricos.
 * 
 * @return Apontador para a entidade do tipo gestor de históricos.
 */
GestorHistory* createGestorHistory();

/**
 * @brief Função que adiciona um histórico à tabela.
 * 
 * @param gestorHistory Apontador para a entidade do tipo gestor de históricos.
 * @param history Histórico a ser adicionado.
 */
void addHistory(GestorHistory* gestorHistory, History* history);

/**
 * @brief Função que remove um histórico da tabela.
 * 
 * @param gestorHistory Apontador para a entidade do tipo gestor de históricos.
 * @param id Id do histórico a ser removido.
 */
void removeHistory(GestorHistory* gestorHistory, long int id);

/**
 * @brief Função que procura um histórico na tabela.
 * 
 * @param gestorHistory Apontador para a entidade do tipo gestor de históricos.
 * @param id Id do histórico a ser procurado.
 * @return Apontador para o histórico encontrado.
 */
History* searchHistory(GestorHistory* gestorHistory, long int id);

/**
 * @brief Função que faz um ciclo sobre todos os históricos da tabela.
 * 
 * @param gestorHistory Apontador para a entidade do tipo gestor de históricos.
 * @param func Função a ser aplicada a cada histórico.
 * @param user_data Dados a serem passados para a função.
 */
void foreachHistory(GestorHistory* gestorHistory, GHFunc func, gpointer user_data);

/**
 * @brief Função que retorna se um histórico existe na tabela.
 * 
 * @param gestorHistory Apontador para a entidade do tipo gestor de históricos.
 * @param id Id do histórico a ser procurado.
 * @return True se o histórico existe, false caso contrário.
 */
bool containsHistoryID(GestorHistory* gestorHistory, long int id);

/**
 * @brief Função que valida se uma lista de ids de históricos existe na tabela.
 * 
 * @param gestorHistory Apontador para a entidade do tipo gestor de históricos.
 * @param idList Lista de ids a serem validados.
 * @param N Tamanho da lista.
 * @return True se todos os ids existem, false caso contrário.
 */
bool validateHistoryIDs(GestorHistory* gestorHistory, long int *idList, int N);


/**
 * @brief Função que adiciona uma lista de top 10 artistas mais ouvidos numa dada semana na tabela de semanas.
 * 
 * @param gestorHistory Apontador para a entidade do tipo gestor de históricos.
 * @param week uma chave que representa a semana.
 * @param top10List lista de top 10 artistas.
 */
void addWeekToTop10(GestorHistory* gestorHistory, const char* week, GList* top10List);

/**
 * @brief Função que faz sort de artistas conforme a reprodução de cada artista.
 * 
 * @param a Artista "A" a ser comparado.
 * @param b Artista "B" a ser comparado.
 */
gint compareArtistData(ArtistData* a, ArtistData* b);

/**
 * @brief Função que cria a lista de top 10 artistas já ordenados conforme a reprodução.
 * 
 * @param artistTable Apontador para a entidade do tipo ArtistTable
 * @return GList que contém a lista dos top 10 artistas
 */
GList* extractTop10Artists(ArtistTable* artistTable);

/**
 * @brief Função que popula a tabela que representa para cada semana os top 10 artistas já pré-calculados.
 * 
 * @param gestorHistory Apontador para a entidade do tipo gestor de históricos.
 */
void populateWeekTop10(GestorHistory* gestorHistory);

/**
 * @brief Função que devolve o artista que esteve no top 10 mais vezes.
 * 
 * @param gestorHistory Apontador para a entidade do tipo gestor de históricos.
 * @param max_count Contador para saber quantas vezes o artista esteve no top 10
 * 
 * @return Uma entidade do tipo ArtistData que representa o artista que esteve no top 10 mais vezes.
 */
ArtistData* findMostFrequentArtist(GestorHistory* gestorHistory, int* max_count);

/**
 * @brief Função auxiliar que faz a contagem para cada Artista o número de vezes que esteve no top 10.
 * 
 * @param gestorHistory Apontador para a entidade do tipo gestor de históricos.
 * @param artist_id Id do artista.
 * 
 * @return Uma entidade do tipo ArtistData que representa o artista que esteve no top 10 mais vezes.
 */
void updateArtistCount(GestorHistory* gestorHistory, long int artist_id);



/**
 * @brief Função para determinar quantas vezes cada artista esteve no top 10, com ou sem intervalo de semanas.
 * 
 * @param gestorHistory Apontador para a entidade do tipo gestor de históricos.
 * @param start_week Intervalo de quando a semana começa (pondendo ser null).
 * @param end_week Intervalo de quando a semana acaba (podendo ser null).
 * 
 * @return 1 se existem semanas entre o intervalo, 0 se não.
 */
int countTop10Appearances(GestorHistory* gestorHistory, const char* start_week, const char* end_week);

/**
 * @brief Função reseta a size da tabela, de modo a ser utilizada nas próximas vezes
 * 
 * @param gestorHistory Apontador para a entidade do tipo gestor de históricos.
 */
void resetArtistCountTable(GestorHistory* gestorHistory);

/**
 * @brief Função que cria uma tabela de artistas.
 * 
 * @return Apontador para a entidade do tipo tabela de artistas.
 */
ArtistTable* createArtistTable();

/**
 * @brief Função que destroi a tabela de artistas.
 * 
 * @param value Apontador para a entidade do tipo tabela de artistas.
 */
void destroyArtistTable(gpointer value);

/**
 * @brief Função que adiciona um artista e a sua duração ouvida numa semana.
 * 
 * @param gestorHistory Apontador para a entidade do tipo gestor de históricos.
 * @param week_key Chave da semana.
 * @param artist_id Id do artista.
 * @param duration Duração ouvida.
 * @param type Tipo do artista.
 */
void addArtistDurationWeek(GestorHistory* gestorHistory, char* week_key, long int artist_id, int duration, ArtistType type);

/**
 * @brief Função que adiciona um artista à tabela de artistas.
 * 
 * @param artistTable Apontador para a entidade do tipo tabela de artistas.
 * @param artist_id Id do artista.
 * @param duration Duração ouvida.
 * @param type Tipo do artista.
 */
void addToArtistTable(ArtistTable* artistTable, long int artist_id, int duration, ArtistType type);

/**
 * @brief Função que procura os genéros ouvidos por um utilizador.
 * 
 * @param gestorHistory Apontador para a entidade do tipo gestor de históricos.
 * @param username Nome do utilizador.
 * @return Apontador para a estrutura dos genéros ouvidos.
 */
GenresListened* searchGenresListened(GestorHistory* gestorHistory, char* username);

/**
 * @brief Função que adiciona um género à lista de géneros ouvidos por um utilizador.
 * 
 * @param gestorHistory Apontador para a entidade do tipo gestor de históricos.
 * @param username Nome do utilizador.
 * @param genre Género a ser adicionado.
 */
void addGenresListened(GestorHistory* gestorHistory, char* username, char* genre);

/**
 * @brief Função que devolve a lista de géneros ouvidos por um utilizador.
 * 
 * @param gestorHistory Apontador para a entidade do tipo gestor de históricos.
 * @return Apontador para a lista de géneros ouvidos.
 */
GPtrArray* getGenresListenedArray(GestorHistory* gestorHistory);

/**
 * @brief Função que devolve uma entidade do tipo géneros ouvidos de um array.
 * 
 * @param gestorHistory Apontador para a entidade do tipo gestor de históricos.
 * @param index Índice do género a ser devolvido.
 * @return Apontador para uma entidade do tipo géneros ouvidos.
 */
GenresListened* getGenresListenedFromArray(GestorHistory* gestorHistory, int index);

/**
 * @brief Função que adiciona á entidade do tipo géneros ouvidos um género de um utilizador semelhante.
 * @param gestorHistory Apontador para a entidade do tipo gestor de históricos.
 * @param targetUser Apontador para a entidade do tipo géneros ouvidos.
 */
void addSimilarUsers(GestorHistory* gestorHistory, GenresListened* targetUser);

/**
 * @brief Função que devolve a lista de utilizadores semelhantes.
 * 
 * @param gestorHistory Apontador para a entidade do tipo gestor de históricos.
 * @return Apontador para a lista de utilizadores semelhantes.
 */
GPtrArray* getSimilarUsersArray(GestorHistory* gestorHistory);

/**
 * @brief Função que devolve uma entidade do tipo géneros ouvidos de um array de utilizadores semelhantes.
 * 
 * @param gestorHistory Apontador para a entidade do tipo gestor de históricos.
 * @param index Índice do utilizador a ser devolvido.
 * @return Apontador para uma entidade do tipo géneros ouvidos.
 */
GenresListened* getSimilarUsersFromArray(GestorHistory* gestorHistory, int index);

/**
 * @brief Função que compara dois utilizadores semelhantes por tamanho e similaridade.
 * 
 * @param a Apontador para o primeiro utilizador semelhante.
 * @param b Apontador para o segundo utilizador semelhante.
 * @return 0 se os utilizadores são iguais, um número negativo se o primeiro utilizador é menor que o segundo e um número positivo se o primeiro utilizador é maior que o segundo.
 */
int compareUsersBySizeAndSimilarity(gconstpointer a, gconstpointer b);

/**
 * @brief Função que ordena utilizadores semelhantes por tamanho e similaridade.
 * 
 * @param gestorHistory Apontador para a entidade do tipo gestor de históricos.
 */
void sortSimilarUsers(GestorHistory* gestorHistory);

/**
 * @brief Função que altera o tamanho do array de utilizadores semelhantes a 0.
 * 
 * @param gestorHistory Apontador para a entidade do tipo gestor de históricos.
 */
void resetSimilarUsersArray(GestorHistory* gestorHistory);

/**
 * @brief Função que liberta a memória alocada para a lista de géneros ouvidos.
 * 
 * @param gestorHistory Apontador para a entidade do tipo gestor de históricos.
 */
void freeSimilarUsersArray(GestorHistory* gestorHistory);

/**
 * @brief Função que liberta a memória alocada para o gestor de históricos.
 * 
 * @param gestorHistory Apontador para a entidade do tipo gestor de históricos.
 */
void freeGestorHistory(GestorHistory* gestorHistory);

#endif