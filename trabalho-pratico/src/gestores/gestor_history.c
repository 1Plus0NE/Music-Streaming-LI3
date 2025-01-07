#include "../../include/gestores/gestor_history.h"

// Estrutura do gestor de histórico.
struct gestor_history{
    GHashTable* table;
    GHashTable* genres_listened_table;
    GHashTable* week_artist_duration_table; // pre-calcula todos os artistas numa dada semana
    GPtrArray* genres_listened_array;
    GPtrArray* similar_users_array;
    GHashTable* week_top10_table; // top 10 artistas para cada semana
    GHashTable* artist_count_table; // table auxiliar para determinar o artista que esteve + vezes no top10
};

struct artist_table{
    GHashTable* artist_ht; // Key: artist_id, Valor: ArtistData
};

// Função para criar um gestor de histórico.
GestorHistory* createGestorHistory(){
    GestorHistory* gestorHistory = malloc(sizeof(GestorHistory));
    if(gestorHistory == NULL){
        perror("Falha ao criar a struct GestorHistory.\n");
        free(gestorHistory);
        return NULL;
    }

    gestorHistory -> table = g_hash_table_new_full(g_int_hash, g_int_equal, free, freeHistoryInTable);
    if(gestorHistory -> table == NULL){
        perror("Falha ao criar a tabela de hashing de histórico.\n");
        free(gestorHistory);
        return NULL;
    }
    gestorHistory -> week_artist_duration_table = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, destroyArtistTable);
    if(gestorHistory -> week_artist_duration_table == NULL){
        perror("Falha ao criar a tabela de hashing de artistas por semana.\n");
        g_hash_table_destroy(gestorHistory -> table);
        free(gestorHistory);
        return NULL;
    }
    gestorHistory -> genres_listened_table = g_hash_table_new_full(g_str_hash, g_str_equal, free, freeGenresListenedInTable);
    if(gestorHistory -> genres_listened_table == NULL){
        perror("Falha ao criar a tabela de generos ouvidos\n");
        g_hash_table_destroy(gestorHistory -> table);
        g_hash_table_destroy(gestorHistory -> week_artist_duration_table);
        free(gestorHistory);
        return NULL;
    }

    gestorHistory -> genres_listened_array = g_ptr_array_new();
    if(gestorHistory -> genres_listened_array == NULL){
        perror("Falha ao criar o array de musicas ouvidas\n");
        g_hash_table_destroy(gestorHistory -> table);
        g_hash_table_destroy(gestorHistory -> week_artist_duration_table);
        g_hash_table_destroy(gestorHistory -> genres_listened_table);
        free(gestorHistory);
        return NULL;
    }

    gestorHistory -> similar_users_array = g_ptr_array_new();
    if(gestorHistory -> similar_users_array == NULL){
        perror("Falha ao criar o array de utilizadores semelhantes\n");
        g_hash_table_destroy(gestorHistory -> table);
        g_hash_table_destroy(gestorHistory -> week_artist_duration_table);
        g_hash_table_destroy(gestorHistory -> genres_listened_table);
        g_ptr_array_free(gestorHistory -> genres_listened_array, TRUE);
    }

    gestorHistory -> week_top10_table = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, (GDestroyNotify)g_list_free);
    if(gestorHistory -> week_top10_table == NULL){
        perror("Falha ao criar a tabela de top10.\n");
        g_hash_table_destroy(gestorHistory -> table);
        g_hash_table_destroy(gestorHistory -> week_artist_duration_table);
        g_hash_table_destroy(gestorHistory -> genres_listened_table);
        g_ptr_array_free(gestorHistory -> genres_listened_array, TRUE);
        g_ptr_array_free(gestorHistory-> similar_users_array, TRUE);
    }

    gestorHistory-> artist_count_table = g_hash_table_new_full(g_int_hash, g_int_equal, free, free);
    if(gestorHistory -> artist_count_table == NULL){
        perror("Falha ao criar a tabela de artistas auxiliar.\n");
        g_hash_table_destroy(gestorHistory -> table);
        g_hash_table_destroy(gestorHistory -> week_artist_duration_table);
        g_hash_table_destroy(gestorHistory -> genres_listened_table);
        g_ptr_array_free(gestorHistory -> genres_listened_array, TRUE);
        g_ptr_array_free(gestorHistory-> similar_users_array, TRUE);
        g_hash_table_destroy(gestorHistory -> week_top10_table);
    }

    return gestorHistory;
}

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

// Função que adiciona uma lista de top 10 artistas mais ouvidos numa dada semana na tabela de semanas
void addWeekToTop10(GestorHistory* gestorHistory, const char* week, GList* top10List){
    char* weekKey = g_strdup(week);
    g_hash_table_insert(gestorHistory->week_top10_table, weekKey, top10List);
}

// Função que faz sort de artistas conforme a reprodução de cada artista.
gint compareArtistData(ArtistData* a, ArtistData* b){
    int total_repA = getArtistTotalReproduction(a);
    int total_repB = getArtistTotalReproduction(b);
    if(total_repA != total_repB){
        return total_repB - total_repA; 
    }
    long int idA = getArtistIdFromData(a);
    long int idB = getArtistIdFromData(b);

    return (idA > idB) - (idA < idB); 
}

// Função que cria a lista de top 10 artistas já ordenados conforme a reprodução.
GList* extractTop10Artists(ArtistTable* artistTable){
    GList* artist_list = NULL;

    // Iterar pela tabela de artistas contidos em cada semana e colecioná-los
    GHashTableIter artist_iter;
    gpointer key, value;
    g_hash_table_iter_init(&artist_iter, artistTable->artist_ht);

    while(g_hash_table_iter_next(&artist_iter, &key, &value)){
        ArtistData* artist = (ArtistData*)value;
        artist_list = g_list_prepend(artist_list, artist);
    }

    // Ordenar a lista conforme a reprodução de cada artista
    artist_list = g_list_sort(artist_list, (GCompareFunc)compareArtistData);

    // Truncar a lista para apenas 10 artistas.
    GList* top10List = NULL;
    GList* iter_node = artist_list;
    int count = 0;
    while(iter_node != NULL && count < 10){
        top10List = g_list_append(top10List, iter_node->data);
        iter_node = iter_node->next;
        count++;
    }

    g_list_free(artist_list);

    return top10List;
}

// Função que popula a tabela que representa para cada semana os top 10 artistas já pré-calculados
void populateWeekTop10(GestorHistory* gestorHistory){
    // Iterar pela tabela "week_artist_duration_table" que contém para cada semana todos os artistas
    GHashTableIter week_iter;
    gpointer week_key, artist_table_value;

    g_hash_table_iter_init(&week_iter, gestorHistory->week_artist_duration_table);
    while(g_hash_table_iter_next(&week_iter, &week_key, &artist_table_value)){
        char* week = (char*)week_key;
        ArtistTable* artistTable = (ArtistTable*)artist_table_value;

        // Cria a lista de top 10
        GList* top10List = extractTop10Artists(artistTable);

        // Adiciona a lista de top 10 à respetiva semana
        addWeekToTop10(gestorHistory, week, top10List);
    }
}

// Função que devolve o artista que esteve no top 10 mais vezes
ArtistData* findMostFrequentArtist(GestorHistory* gestorHistory, int* max_count){
    if(!gestorHistory || !gestorHistory->artist_count_table) return NULL;

    GHashTableIter iter;
    gpointer key, value;
    ArtistData* most_frequent_artist = NULL;
    *max_count = 0;

    g_hash_table_iter_init(&iter, gestorHistory->artist_count_table);
    while(g_hash_table_iter_next(&iter, &key, &value)){
        long int artist_id = *(long int*)key;
        int count = *(int*)value;

        ArtistData* artistData = NULL;
        GHashTableIter week_iter;
        gpointer week_key, week_value;

        g_hash_table_iter_init(&week_iter, gestorHistory->week_artist_duration_table);
        while(g_hash_table_iter_next(&week_iter, &week_key, &week_value)){
            ArtistTable* artist_table = (ArtistTable*)week_value;
            artistData = g_hash_table_lookup(artist_table->artist_ht, &artist_id);
            if(artistData) break; 
        }

        if(!artistData) continue; // Se o artista não foi encontrado, continuamos

        // Critério para definir o artista que teve no top 10 mais vezes
        if(count > *max_count || 
            (count == *max_count && getArtistIdFromData(artistData) < getArtistIdFromData(most_frequent_artist))) {
            most_frequent_artist = artistData;
            *max_count = count;
        }
    }

    return most_frequent_artist;
}

// Função auxiliar que faz a contagem para cada Artista o número de vezes que esteve no top 10
void updateArtistCount(GestorHistory* gestorHistory, long int artist_id){
    if(!gestorHistory || !gestorHistory->artist_count_table) return;

    int* count = g_hash_table_lookup(gestorHistory->artist_count_table, &artist_id);
    if(count){
        (*count)++;
    }else{
        long int* key = malloc(sizeof(long int));
        int* value = malloc(sizeof(int));
        if (!key || !value) {
            perror("Error allocating memory for artist count");
            free(key);
            free(value);
            return;
        }
        *key = artist_id;
        *value = 1;
        g_hash_table_insert(gestorHistory->artist_count_table, key, value);
    }
}

// Função para determinar quantas vezes cada artista esteve no top 10, com ou sem intervalo de semanas
int countTop10Appearances(GestorHistory* gestorHistory, const char* start_week, const char* end_week){
    if(!gestorHistory || !gestorHistory->week_top10_table) return 0;

    GHashTableIter iter;
    gpointer week_key, top10_list;
    bool found_weeks_in_interval = false; // processo de verificação se existem semanas entre o intervalo 

    g_hash_table_iter_init(&iter, gestorHistory->week_top10_table);
    while (g_hash_table_iter_next(&iter, &week_key, &top10_list)){
        char* week = (char*)week_key;

        // Filter as semanas baseado no intervalo fornecido
        if((start_week && strcmp(week, start_week) < 0) ||  // Week < start_week
            (end_week && strcmp(week, end_week) > 0)) {      // Week > end_week
            continue;
        }
        
        found_weeks_in_interval = true; // foi encontrada pelo menos uma semana

        // Atualização do contador para cada artista que esteve no top 10
        GList* list = (GList*)top10_list;
        for (GList* node = list; node != NULL; node = node->next) {
            ArtistData* artistData = (ArtistData*)node->data;
            updateArtistCount(gestorHistory, getArtistIdFromData(artistData));
        }
    }
    // retorna 1 ou 0 dependendo se foi encontrada uma semana ou não
    return found_weeks_in_interval ? 1 : 0;
}

// Função reseta a size da tabela, de modo a ser utilizada nas próximas vezes
void resetArtistCountTable(GestorHistory* gestorHistory) {
    if (gestorHistory && gestorHistory->artist_count_table) {
        g_hash_table_remove_all(gestorHistory->artist_count_table);
    }
}

// Função que cria uma tabela de artistas.
ArtistTable* createArtistTable(){
    ArtistTable* table = malloc(sizeof(ArtistTable));
    table -> artist_ht = g_hash_table_new_full(g_int_hash, g_int_equal, free, free);
    return table;
}

// funcao que destroi a tabela de artistas
void destroyArtistTable(gpointer value){
    if(value){
        ArtistTable* artist_table = (ArtistTable*) value;

        // Destruir a tabela de artistas
        if(artist_table->artist_ht){
            g_hash_table_destroy(artist_table->artist_ht);
        }

        // Liberar o próprio objeto ArtistTable
        free(artist_table);
    }
}

// Função que adiciona um artista e a sua duração ouvida numa semana.
void addArtistDurationWeek(GestorHistory* gestorHistory, char* week_key, long int artist_id, int duration, ArtistType type){
    ArtistTable* artist_duration_table = g_hash_table_lookup(gestorHistory -> week_artist_duration_table, week_key);
    if(!artist_duration_table){
        artist_duration_table = createArtistTable();
        g_hash_table_insert(gestorHistory -> week_artist_duration_table, g_strdup(week_key), artist_duration_table);
    }
    addToArtistTable(artist_duration_table, artist_id, duration, type);
}

// Função que adiciona um artista à tabela de artistas.
void addToArtistTable(ArtistTable* artistTable, long int artist_id, int duration, ArtistType type){
    long int key_lookup = artist_id;
    ArtistData* artist_data_found = g_hash_table_lookup(artistTable -> artist_ht, &key_lookup);
    if(!artist_data_found){
        long int* key = malloc(sizeof(long int));
        if(!key){
            perror("Erro ao alocar memória para a chave do histórico");
            return;
        }
        *key = artist_id;
        ArtistData* artist_data = createArtistData(artist_id, duration, type);
        g_hash_table_insert(artistTable -> artist_ht, key, artist_data);
    }else{
        int duration_found = getArtistTotalReproduction(artist_data_found);
        setArtistTotalReproduction(artist_data_found, duration_found + duration);
    }
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
        freeStringArray(genres, size);
        free(listened);
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
    
    //g_ptr_array_set_size(gestorHistory->similar_users_array, 0);

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
                free(newUserGenresListened);
            }
            freeStringArray(newUserGenres, newUserSize);
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

// Função que ordena todos os elementos do Array de utilizadores semelhantes
void sortSimilarUsers(GestorHistory* gestorHistory){
    if(gestorHistory && gestorHistory -> similar_users_array){
        g_ptr_array_sort(gestorHistory -> similar_users_array, compareUsersBySizeAndSimilarity);
    }
}

// Função que seta a size do array de utilizadores semelhantes a 0
void resetSimilarUsersArray(GestorHistory* gestorHistory){
    if(gestorHistory -> similar_users_array){
        g_ptr_array_set_size(gestorHistory->similar_users_array, 0);
    }
}

// Função liberta a memoria alocada de um GPtrArray para utilizadores semelhantes
void freeSimilarUsersArray(GestorHistory* gestorHistory){
    if(gestorHistory -> similar_users_array){
        g_ptr_array_free(gestorHistory -> similar_users_array, TRUE);
    }
}

// Função que liberta a memória alocada para a tabela de histórico.
void freeGestorHistory(GestorHistory* gestorHistory){
    if(gestorHistory){
        if(gestorHistory -> table){
            g_hash_table_destroy(gestorHistory -> table);
        }
        if(gestorHistory -> genres_listened_table){
            g_hash_table_destroy(gestorHistory -> genres_listened_table);
        }
        if(gestorHistory -> week_top10_table){
            g_hash_table_destroy(gestorHistory -> week_top10_table);
        }
        if(gestorHistory -> week_artist_duration_table){
            g_hash_table_destroy(gestorHistory -> week_artist_duration_table);
        }
        if(gestorHistory->artist_count_table){
            g_hash_table_destroy(gestorHistory->artist_count_table);
        }
        if(gestorHistory -> genres_listened_array){
            g_ptr_array_free(gestorHistory->genres_listened_array, TRUE);
        }
        if(gestorHistory -> similar_users_array){
            g_ptr_array_set_size(gestorHistory -> similar_users_array, 0);
            freeSimilarUsersArray(gestorHistory); 
        }

        free(gestorHistory);
    }
}