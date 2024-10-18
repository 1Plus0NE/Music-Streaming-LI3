#ifndef GESTOR_USER_H
#define GESTOR_USER_H
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include "../entidades/user.h"
#include <glib.h>

// função para criar uma tabela de utilizadores.
void createUserTable();

// função que adiciona um utilizador á tabela de utilizadores.
void addUser(GHashTable* table, User* user);

// função que remove um utilizador da tabela de utilizadores.
void removeUser(GHashTable* table, char* username);

// função que encontra um utilizador pelo username na tabela.
User* searchUser(GHashTable* table, char* username);

// função que libera a memória alocada para a tabela de utilizadores.
void freeUserTable(GHashTable* table);

#endif