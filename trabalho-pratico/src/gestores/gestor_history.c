#include "../../include/gestores/gestor_history.h"

// Estrutura do gestor de histórico.
struct gestor_history{
    GHashTable* table;
    GHashTable* genres_listened_table;
    GPtrArray* genres_listened_array;
    GPtrArray* similar_users_array;
};

// Função para criar um gestor de histórico.
GestorHistory* createGestorHistory(){
    GestorHistory* gestorHistory = malloc(sizeof(GestorHistory));
    if(gestorHistory == NULL){
        perror("Falha ao criar a struct GestorHistory.\n");
        free(gestorHistory);
        return NULL;
    }

    gestorHistory -> table = g_hash_table_new(g_int_hash, g_int_equal);
    if(gestorHistory -> table == NULL){
        perror("Falha ao criar a tabela de hashing de histórico.\n");
        free(gestorHistory);
        return NULL;
    }

    gestorHistory -> genres_listened_table = g_hash_table_new(g_str_hash, g_str_equal);
    if(gestorHistory -> genres_listened_table == NULL){
        perror("Falha ao criar a tabela de generos ouvidos\n");
        g_hash_table_destroy(gestorHistory -> table);
        free(gestorHistory);
        return NULL;
    }

    gestorHistory -> genres_listened_array = g_ptr_array_new_with_free_func((GDestroyNotify)freeGenresListened);
    if(gestorHistory -> genres_listened_array == NULL){
        perror("Falha ao criar o array de musicas ouvidas\n");
        g_hash_table_destroy(gestorHistory -> table);
        g_hash_table_destroy(gestorHistory -> genres_listened_table);
        free(gestorHistory);
        return NULL;
    }

    gestorHistory -> similar_users_array = g_ptr_array_new();
    if(gestorHistory -> similar_users_array == NULL){
        perror("Falha ao criar o array de utilizadores semelhantes\n");
        g_hash_table_destroy(gestorHistory -> table);
        g_hash_table_destroy(gestorHistory -> genres_listened_table);
        g_ptr_array_free(gestorHistory->genres_listened_array, TRUE);
    }

    return gestorHistory;
}

/*
// Função que adiciona um histórico à tabela.
void addHistory(GestorHistory* gestorHistory, History* history){
    if(gestorHistory && gestorHistory -> table){
        long int* key = malloc(sizeof(long int));
        if(!key){
            perror("Erro ao alocar memória para a chave do histórico");
            return;
        }
        *key = getHistoryId(history);
        g_hash_table_insert(gestorHistory -> table, key, history);
    }
}
*/
void addHistory(GestorHistory* gestorHistory, History* history){
    if(gestorHistory && gestorHistory -> table){
        g_hash_table_insert(gestorHistory -> table, getHistoryId(history), history);
    }
}


// Função que remove um histórico da tabela.
void removeHistory(GestorHistory* gestorHistory, long int id){
    if(gestorHistory && gestorHistory -> table){
        g_hash_table_remove(gestorHistory -> table, &id);
    }
}

// Função que encontra um histórico pelo id na tabela.
History* searchHistory(GestorHistory* gestorHistory, long int id){
    if(gestorHistory && gestorHistory -> table){
        return (History*) g_hash_table_lookup(gestorHistory -> table, &id);
    }
    return NULL;
}

// Função que aplica uma função callback em cada item da tabela de histórico.
void foreachHistory(GestorHistory* gestorHistory, GHFunc func, gpointer user_data){
    if(gestorHistory && gestorHistory -> table && func){
        g_hash_table_foreach(gestorHistory -> table, func, user_data);
    }
}

// Função que verifica se a chave existe na tabela de histórico.
bool containsHistoryID(GestorHistory* gestorHistory, long int id){
    if(gestorHistory && gestorHistory -> table){
        return g_hash_table_contains(gestorHistory -> table, &id);
    }
    return false;
}

// Função que verifica se todos os IDs existem na tabela de histórico.
bool validateHistoryIDs(GestorHistory* gestorHistory, long int* idList, int N){
    if(gestorHistory && gestorHistory -> table){
        for(int i = 0; i < N; i++){
            if(!containsHistoryID(gestorHistory, idList[i])){
                return false;
            }
        }
        return true;
    }
    return false;
}

// Função que encontra um GenresListened pelo username na tabela
GenresListened* searchGenresListened(GestorHistory* gestorHistory, char* username){
    if(gestorHistory && gestorHistory -> genres_listened_table){
        return (GenresListened*) g_hash_table_lookup(gestorHistory -> genres_listened_table, username);
    }
    return NULL;
}

// Função que adiciona uma estrutura GenresListened na hashtable
void addGenresListened(GestorHistory* gestorHistory, char* username, char* genre){
    // Verificar se já existe uma entidade GenresListened através do username
    GenresListened* genresListened = searchGenresListened(gestorHistory, username);
    if(!genresListened){
        // No caso de não existir
        char** genres = NULL;
        int* listened = NULL;
        int size = 0;
        updateGenresListenedArray(&genres, &listened, &size, genre);

        genresListened = createGenresListened(username, genres, listened, size);
        char* usernameKey = getGenresListenedUsername(genresListened);
        g_hash_table_insert(gestorHistory -> genres_listened_table, usernameKey, genresListened);
        g_ptr_array_add(gestorHistory -> genres_listened_array, genresListened);
    }
    else{
        // getters
        char** genresGL = getGenresListenedArrayGenres(genresListened);
        int* listenedGL = getGenresListenedArrayListened(genresListened);
        int sizeGL = getGenresListenedArraysSize(genresListened);
        
        updateGenresListenedArray(&genresGL, &listenedGL, &sizeGL, genre); // Aqui estamos a atualizar os nossos getters
        //setters
        setGenresListenedArrayGenres(genresListened, genresGL, sizeGL); // atualizar a info dos generos
        setGenresListenedArrayListened(genresListened, listenedGL, sizeGL); // atualizar a info das musicas ouvidas
        freeStringArray(genresGL, sizeGL);
        free(listenedGL);

    }
}

// Função que retorna o array que contem todos os elementos da estrutura GenresListened
GPtrArray* getGenresListenedArray(GestorHistory* gestorHistory){
    return gestorHistory->genres_listened_array;
}

// Função que retorna um elemento do array que armazena a estrutura de GenresListened
GenresListened* getGenresListenedFromArray(GestorHistory* gestorHistory, int index){
    if(gestorHistory && gestorHistory->genres_listened_array){
        return (GenresListened*) g_ptr_array_index(gestorHistory->genres_listened_array, index);
    }
    return NULL;
}

// Função que dá store de utilizadores semelhantes temporariamente
void addSimilarUsers(GestorHistory* gestorHistory, GenresListened* targetUser){
    
    g_ptr_array_set_size(gestorHistory->similar_users_array, 0);

    // Dados sobre o user recebido
    char* targetUserUsername = getGenresListenedUsername(targetUser);
    char** targetUserGenres = getGenresListenedArrayGenres(targetUser);
    int* targetUserGenresListened = getGenresListenedArrayListened(targetUser);
    int targetUserSize = getGenresListenedArraysSize(targetUser);

    // Array de GenresListened populado no parsing
    GPtrArray* genresListenedArr = getGenresListenedArray(gestorHistory);

    // Iterar pelo array
    for(guint i = 0; i < genresListenedArr->len; i++){
        // Dados de um possível user a ser recomendado
        GenresListened* newUser = getGenresListenedFromArray(gestorHistory, i);
        char* newUserUsername = getGenresListenedUsername(newUser);
        if(strcmp(newUserUsername, targetUserUsername) != 0){
            char** newUserGenres = getGenresListenedArrayGenres(newUser);
            int newUserSize = getGenresListenedArraysSize(newUser);

            // Verificação se este newUser faz match de generos com o targetUser
            if(allGenresMatch(targetUserGenres, targetUserSize, newUserGenres, newUserSize)){

                // Utilizado para calcular a similaridade
                int* newUserGenresListened = getGenresListenedArrayListened(newUser);
                int similarityScore = calculateSimilarityScore(targetUserGenres, targetUserGenresListened, targetUserSize, 
                                                                newUserGenres, newUserGenresListened, newUserSize);

                setSimilarityScore(newUser, similarityScore); // Atualizar a similaridade do utilizador
                // Utilizadores semelhantes já filtrados
                g_ptr_array_add(gestorHistory->similar_users_array, newUser);
                freeStringArray(newUserGenres, newUserSize);
            }

        }
        free(newUserUsername);
    }
    free(targetUserUsername);
    freeStringArray(targetUserGenres, targetUserSize);
    free(targetUserGenresListened);
}

// Função que retorna o array que contem todos os elementos da estrutura GenresListened filtrados
GPtrArray* getSimilarUsersArray(GestorHistory* gestorHistory){
    return gestorHistory->similar_users_array;
}

// Função que retorna um elemento filtrado do array que armazena a estrutura de GenresListened
GenresListened* getSimilarUsersFromArray(GestorHistory* gestorHistory, int index){
    if(gestorHistory && gestorHistory->similar_users_array){
        return (GenresListened*) g_ptr_array_index(gestorHistory->similar_users_array, index);
    }
    return NULL;
}

// Função de sorting para os utilizadores semelhantes
int compareUsersBySizeAndSimilarity(gconstpointer a, gconstpointer b){
    const GenresListened* userA = *(const GenresListened**)a;
    const GenresListened* userB = *(const GenresListened**)b;

    int sizeA = getGenresListenedArraysSize(userA);
    int sizeB = getGenresListenedArraysSize(userB);

    // Compare by size (descending order)
    if(sizeA != sizeB){
        return sizeB - sizeA;
    }

    int similarityA = getGenresListenedSimilarity(userA);
    int similarityB = getGenresListenedSimilarity(userB);

    // Compare by similarity (ascending order)
    if(similarityA != similarityB){
        return similarityA - similarityB;
    }

    char* usernameA = getGenresListenedUsername(userA);
    long idA = strtol(usernameA + 1, NULL, 10);
    free(usernameA);
    
    char* usernameB = getGenresListenedUsername(userB);
    long idB = strtol(usernameB + 1, NULL, 10);
    free(usernameB);

    // Compare by numeric order of IDs (ascending order)
    return (idA > idB) - (idA < idB);
}

void sortSimilarUsers(GestorHistory* gestorHistory){
    if(gestorHistory && gestorHistory -> similar_users_array){
        g_ptr_array_sort(gestorHistory -> similar_users_array, compareUsersBySizeAndSimilarity);
    }
}

// Função liberta a memoria alocada de um GPtrArray para utilizadores semelhantes
void freeSimilarUsersArray(GestorHistory* gestorHistory){
    if(gestorHistory -> similar_users_array){
        g_ptr_array_free(gestorHistory -> similar_users_array, FALSE);
    }
}

// Função que liberta a memória alocada para a tabela de histórico.
void freeGestorHistory(GestorHistory* gestorHistory){
    if(gestorHistory){
        if(gestorHistory -> table){
            g_hash_table_foreach_remove(gestorHistory -> table, freeHistoryInTable, NULL);
            g_hash_table_destroy(gestorHistory -> table);
        }
        if(gestorHistory -> genres_listened_table){
            g_hash_table_destroy(gestorHistory -> genres_listened_table);
        }
        if(gestorHistory -> genres_listened_array){
            g_ptr_array_free(gestorHistory->genres_listened_array, TRUE);
        }
        if(gestorHistory -> similar_users_array){
            freeSimilarUsersArray(gestorHistory); 
        }

        free(gestorHistory);
    }
}

