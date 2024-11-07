#include "../../include/gestores/gestor_artist.h"

// função para criar uma tabela de artistas.
GHashTable* createArtistTable(){
    GHashTable* table = g_hash_table_new(g_int_hash, g_int_equal);
    if (table == NULL) {
        perror("Falha ao criar a tabela de hashing de artistas.\n");
        return NULL;
    }
    return table;
}

// função que adiciona um artista á tabela de artistas.
void addArtist(GHashTable* table, Artist* artist){
    g_hash_table_insert(table, getArtistId(artist), artist);
}

// função que remove um artista da tabela de artistas.
void removeArtist(GHashTable* table, long int id){
    g_hash_table_remove(table, &id);
}

// função que encontra um artista pelo id na tabela.
Artist* searchArtist(GHashTable* table, long int id){
    return (Artist*) g_hash_table_lookup(table, &id);
}

// função que libera a memória alocada para a tabela de artistas.
void freeArtistTable(GHashTable* table){
    g_hash_table_foreach_remove(table,freeArtistInTable,NULL);
    g_hash_table_destroy(table);
}

// Função que verifica se a chave existe na tabela de artistas.
bool containsArtistID(GHashTable* table, long int id){
    return g_hash_table_contains(table, &id);
}

// Função que verifica se todos a lista de ids existe na tabela de artistas.
bool validateArtistIDs(GHashTable *table, long int *idList, int N){
    for (int i=0;i<N;i++){
        if (!containsArtistID(table, idList[i])){
            return false; 
        }
    }
    return true; 
}

// Função que percorre a Hash Table e insere cada artista na lista Discography
Discography* fillWithArtists(GHashTable* table, Discography* disco){
    g_hash_table_foreach(table, artistFromTableToLL, &disco);
    return disco;
}

// Função  para cada item da Hash Table
void artistFromTableToLL(G_GNUC_UNUSED gpointer artistId, gpointer artistData, gpointer discoPtr){
    
    Artist* artist = (Artist*)artistData;
    Discography** disco = (Discography**)discoPtr;
    long int* idPtr = getArtistId(artist);
    long int id;
    if (idPtr) {
        id = *idPtr; // Transforma o ponteiro em long int
    } else {
        id = 0;  //  Não deve acontecer
    }
    //long int id = (idPtr != NULL) ? *idPtr : -1; //Transformar o ponteiro em long int
    char* name = getArtistName(artist);
    char* country = getArtistCountry(artist);
    ArtistType type = getArtistType(artist);
    
    //*disco = artistInsert(*disco, id, name, country, type);
    artistInsert(disco, id, name, country, type);
    free(name);
    free(country);
}