#include "../../include/gestores/gestor_user.h"

//estrutura de gestor de utilizadores.
struct gestor_user{
    GHashTable* table;
    GHashTable* user_likes_table;
    GPtrArray* user_likes_array;
};

//estrutura do iterador de utilizadores.
struct user_iterator{
    GHashTableIter iter;
    gpointer key;
    gpointer value;
    bool initialized;
};

// função para criar uma tabela de utilizadores.
GestorUser* createGestorUser(){
    GestorUser* gestorUser = malloc(sizeof(GestorUser));
    if(gestorUser == NULL){
        perror("Falha ao criar a struct GestorUser.\n");
        return NULL;
    }

    gestorUser -> table = g_hash_table_new(g_str_hash, g_str_equal);
    if(gestorUser -> table == NULL){
        perror("Falha ao criar a tabela de hashing de utilizadores.\n");
        free(gestorUser);
        return NULL;
    }

    gestorUser -> user_likes_table = g_hash_table_new_full(g_int_hash, g_int_equal, free, NULL);
    if(gestorUser -> user_likes_table == NULL){
        perror("Falha ao criar a tabela de likes\n");
        g_hash_table_destroy(gestorUser -> table);
        free(gestorUser);
        return NULL;
    }

    gestorUser -> user_likes_array = g_ptr_array_new_with_free_func((GDestroyNotify)freeUserLikes);
    if(gestorUser -> user_likes_array == NULL){
        perror("Falha ao criar o array de user likes\n");
        g_hash_table_destroy(gestorUser -> table);
        g_hash_table_destroy(gestorUser -> user_likes_table);
        free(gestorUser);
        return NULL;
    }

    return gestorUser;
}

// função que adiciona um utilizador á tabela de utilizadores.
void addUser(GestorUser* gestorUser, User* user){
    char* username = getUserUsername(user);
    if(gestorUser && gestorUser -> table){
        g_hash_table_insert(gestorUser -> table, username, user);
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

// Função que retorna uma entidade userLikes na tabela através da idade
UserLikes* searchUserLikes(GestorUser* gestorUser, int age){
    if(gestorUser && gestorUser->user_likes_table){
        return (UserLikes*) g_hash_table_lookup(gestorUser->user_likes_table, &age);
    }
    return NULL;
}

// Função que adiciona uma estrutura userLike na hashtable
void addUserLikes(GestorUser* gestorUser, char** genres, long int* likes, int size, int age){
    // Verificar se já existe uma entidade userLikes através da idade
    UserLikes* userLikes = searchUserLikes(gestorUser, age);
    if(!userLikes){
        // No caso de não existir
        userLikes = createUserLikes(genres, likes, size, age);
        int* key = malloc(sizeof(int));
        if(!key){
            perror("Erro ao alocar memória para a chave do user_likes.\n");
            return;
        }
        *key = getUserLikesAge(userLikes);
        g_hash_table_insert(gestorUser->user_likes_table, key, userLikes);
        g_ptr_array_add(gestorUser->user_likes_array, userLikes);
    }
    else{
        // getters
        char** genreUL = getUserLikesArrayGenres(userLikes);
        long int* likesUL = getUserLikesArrayLikes(userLikes);
        int sizeUL = getUserLikesSizeArray(userLikes);
        
        updateGenresAndLikes(&genreUL, &likesUL, &sizeUL, genres, likes, size); // Aqui estamos a atualizar os nossos getters
        //setters
        setUserLikesArrayGenres(userLikes, genreUL, sizeUL); // atualizar a info dos generos
        setUserLikesArrayLikes(userLikes, likesUL, sizeUL); // atualizar a info dos likes
        for(int i = 0; i < sizeUL; i++) free(genreUL[i]);
        free(genreUL); 
        free(likesUL);
    }
}

// Função que retorna o array que contem todos os elementos da estrutura userLikes
GPtrArray* getUserLikesArray(GestorUser* gestorUser){
    return gestorUser->user_likes_array;
}

// Função que retorna um elemento do array que armazena a estrutura de userLikes
UserLikes* getUserLikeFromArray(GestorUser* gestorUser, int index){
    if(gestorUser && gestorUser->user_likes_array){
        return (UserLikes*) g_ptr_array_index(gestorUser->user_likes_array, index);
    }
    return NULL;
}

// função que libera a memória alocada para a tabela de utilizadores.
void freeGestorUser(GestorUser* gestorUser){
    if(gestorUser){
        if(gestorUser -> table){
            g_hash_table_foreach_remove(gestorUser -> table, freeUserInTable, NULL);
            g_hash_table_destroy(gestorUser -> table);
        }
        if(gestorUser -> user_likes_table){
            g_hash_table_destroy(gestorUser -> user_likes_table);
        }
        if(gestorUser -> user_likes_array){
            g_ptr_array_free(gestorUser->user_likes_array, TRUE);
        }

        free(gestorUser);
    }
}