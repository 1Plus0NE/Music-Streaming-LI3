#include "../../include/gestores/gestor_user.h"

// função para criar uma tabela de utilizadores.
void createUserTable(){
    return g_hash_table_new(g_str_hash, g_str_equal);
}

// função que adiciona um utilizador á tabela de utilizadores.
void addUser(GHashTable* table, User* user){
    g_hash_table_insert(table, getUserUsername(user), user);
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