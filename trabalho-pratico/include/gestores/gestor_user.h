#ifndef GESTOR_USER_H
#define GESTOR_USER_H
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include "../entidades/user.h"
#include <glib.h>
#include <stdbool.h>

//estrutura de gestor de utilizadores.
typedef struct gestor_user GestorUser;

//estrutura do iterador de utilizadores.
typedef struct user_iterator UserIterator;

typedef void (*GHFunc)(void *key, void *value, void *user_data);

// função para criar uma tabela de utilizadores.
GestorUser* createGestorUser();

// função que adiciona um utilizador á tabela de utilizadores.
void addUser(GestorUser* gestorUser, User* user);

// função que remove um utilizador da tabela de utilizadores.
void removeUser(GestorUser* gestorUser, char* username);

// função que encontra um utilizador pelo username na tabela.
User* searchUser(GestorUser* gestorUser, char* username);

// função que itera sobre todos os utilizadores na tabela de utilizadores
void foreachUser(GestorUser* gestorUser, GHFunc func, gpointer user_data);

// Função que cria um iterator para percorrer os elementos da tabela de utilizadores
UserIterator* createUserIterator(GestorUser* gestorUser);

// Função que retorna um user sobre a função que itera
User* getNextUser(UserIterator* iterator);

// Função que liberta a memória do iterator 
void freeUserIterator(UserIterator* iterator);

// função que libera a memória alocada para a tabela de utilizadores.
void freeGestorUser(GestorUser* gestorUser);

#endif