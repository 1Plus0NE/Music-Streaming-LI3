#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include "gestor_user.h"
#include "user.h"
#include <glib.h>

// função para criar uma tabela de utilizadores.
GHashTable* createUserTable(){
    return g_hash_table_new(g_str_hash, g_str_equal);
}

// função que adiciona um utilizador á tabela de utilizadores.
void addUser(GHashTable* table, User* user){
    g_hash_table_insert(table, user -> username, user);
}

// função que remove um utilizador da tabela de utilizadores.
void removeUser(GHashTable* table, char* username){
    g_hash_table_remove(table, username);
}

// função que encontra um utilizador pelo username na tabela.
User* searchUser(GHashTable* table, char* username){
    return (User*) g_hash_table_lookup(table, username);
}

// função que libera a memória alocada para a tabela de utilizadores.
void freeUserTable(GHashTable* table){
    g_hash_table_destroy(table);
}