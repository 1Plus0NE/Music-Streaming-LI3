#include "../../include/gestores/gestor_user.h"

// função para criar uma tabela de utilizadores.
GHashTable* createUserTable(){
    GHashTable* table = g_hash_table_new(g_str_hash, g_str_equal);
    if (table == NULL) {
        perror("Falha ao criar a tabela de hashing de utilizadores.\n");
        return NULL;
    }

    return table;
}

// função que adiciona um utilizador á tabela de utilizadores.
void addUser(GHashTable* table, User* user){
    char* username = getUserUsername(user);
    g_hash_table_insert(table,username, user);
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
    g_hash_table_foreach_remove(table,freeUserInTable,NULL);
    g_hash_table_destroy(table);
}