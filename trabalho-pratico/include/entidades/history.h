#ifndef HISTORY_H
#define HISTORY_H
#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../utils.h"
#include "glib.h"

//forma de enunciar a entidade histórico.
typedef struct history History;

//enum que representa o atributo plataforma do histórico.
typedef enum {
    DESKTOP,
    MOBILE,
} Platform;

//função para criar uma estrutura da entidade histórico parametrizada.
History* createHistory(long int id, long int user_id, long int music_id, char* timestamp, char* duration, Platform platform);

//função para libertar a memória de uma entidade do tipo histórico.
void freeHistory(History* history);

//função para libertar a memória de uma entidade do tipo histórico contida numa hash table.
gboolean freeHistoryInTable(gpointer key, gpointer value, gpointer user_data);

//função para converter uma string de plataforma para a forma de enum.
Platform stringToPlatform(char* platform_str);

//função para converter uma forma de enum de plataforma para uma string.
char* platformToString(Platform platform);

//função para verificar se uma string é uma plataforma válida.
int isValidPlatform(char* platform_str);

//getters e setters de histórico.
long int* getHistoryId(History* history);

long int getHistoryUserId(History* history);

long int getHistoryMusicId(History* history);

char* getHistoryTimestamp(History* history);

char* getHistoryDuration(History* history);

Platform getHistoryPlatform(History* history);

void setHistoryId(History* history, long int id);

void setHistoryUserId(History* history, long int user_id);

void setHistoryMusicId(History* history, long int music_id);

void setHistoryTimestamp(History* history, char* timestamp);

void setHistoryDuration(History* h, char* duration);

void setHistoryPlatform(History* history, Platform platform);

#endif