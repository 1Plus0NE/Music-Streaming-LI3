#include "../../include/gestores/gestor_user.h"

struct gestor_user{
    GHashTable* table;
};

struct user_iterator{
    GHashTableIter iter;
    gpointer key;
    gpointer value;
    bool initialized;
};

// função para criar uma tabela de utilizadores.
GestorUser* createGestorUser(){
    GestorUser* gestorUser = malloc(sizeof(GestorUser));
    if (gestorUser == NULL) {
        perror("Falha ao criar a struct GestorUser.\n");
        free(gestorUser);
        return NULL;
    }

    gestorUser -> table = g_hash_table_new(g_str_hash, g_str_equal);
    if(gestorUser -> table == NULL){
        perror("Falha ao criar a tabela de hashing de utilizadores.\n");
        free(gestorUser);
        return NULL;
    }
    return gestorUser;
}

// função que adiciona um utilizador á tabela de utilizadores.
void addUser(GestorUser* gestorUser, User* user){
    char* username = getUserUsername(user);
    if(gestorUser && gestorUser -> table){
        g_hash_table_insert(gestorUser -> table,username, user);
    }
}

// função que remove um utilizador da tabela de utilizadores.
void removeUser(GestorUser* gestorUser, char* username){
    if(gestorUser && gestorUser -> table){
        g_hash_table_remove(gestorUser -> table, username);
    }
}

// função que encontra um utilizador pelo username na tabela.
User* searchUser(GestorUser* gestorUser, char* username){
    if(gestorUser && gestorUser -> table){
        return (User*) g_hash_table_lookup(gestorUser -> table, username);
    }
    return NULL;
}

// função que itera sobre todos os utilizadores na tabela de utilizadores
void foreachUser(GestorUser* gestorUser, GHFunc func, gpointer user_data){
    if(gestorUser && gestorUser->table){
        g_hash_table_foreach(gestorUser->table, func, user_data);
    }
}

// Função que itera sobre todos os utilizadores na tabela de utilizadores usando um iter_init
UserIterator* createUserIterator(GestorUser* gestorUser){
    UserIterator* iterator = malloc(sizeof(UserIterator));
    if(!iterator){
        perror("Falha ao alocar memoria para o iterator.\n");
        return NULL;
    }
    g_hash_table_iter_init(&iterator->iter, gestorUser->table);
    iterator->initialized = true;
    return iterator;
}

// Função que retorna um user sobre a função que itera
User* getNextUser(UserIterator* iterator){
    if(!iterator->initialized){
        return NULL;
    }
    if(g_hash_table_iter_next(&iterator->iter, &iterator->key, &iterator->value)){
        return (User*)iterator->value;
    }
    return NULL; 
}

// Função que liberta a memória do iterator 
void freeUserIterator(UserIterator* iterator){
    if(iterator){
        free(iterator);
    }
}

// função que libera a memória alocada para a tabela de utilizadores.
void freeGestorUser(GestorUser* gestorUser){
    if(gestorUser){
        if(gestorUser -> table){
            g_hash_table_foreach_remove(gestorUser -> table, freeUserInTable, NULL);
            g_hash_table_destroy(gestorUser -> table);
        }
        free(gestorUser);
    }
}