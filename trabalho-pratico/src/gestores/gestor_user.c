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
    g_hash_table_insert(table, getUserUsername(user), user);
}

// função que remove um utilizador da tabela de utilizadores.
void removeUser(GHashTable* table, char* username){
    g_hash_table_remove(table, username);
}

// função que encontra um utilizador pelo username na tabela.
User* searchUser(GHashTable* table, char* username){
    return (User*) g_hash_table_lookup(table, &username);
}

// função que libera a memória alocada para a tabela de utilizadores.
void freeUserTable(GHashTable* table){
    g_hash_table_destroy(table);
}

// Função que verifica a existência de uma musica pelo seu id, na tabela de musicas
bool containsMusicID(GHashTable* table, long int id){
    return g_hash_table_contains(table, &id);
}

// Função que verifica se todos os ids das musicas pertencem à tabela
bool validateMusicId(GHashTable* table, long int* id, int N){
    for(int i=0;i<N;i++){
        if(!containsMusicID(table, id[i])==false) return false;
    }
    return true;
}