#include "../include/queries.h"

// Lista ligada para a Query 2
struct discography {
    long int id; // Id do artista/banda
    char* name;
    char* country;
    int duration; // Duracao em segundos
    ArtistType type;
    struct discography* next;
};

// função que responde á query1.
void query1(char* user_username, GHashTable* user_table, FILE* output_file){
    User* user = searchUser(user_table, user_username);

    if(!user){
        fprintf(output_file, "\n");
    }

    int age = calculaIdade(getUserBirthDate(user));

    fprintf(output_file, "%s;%s;%s;%d;%s\n", getUserEmail(user), getUserFirstName(user), getUserLastName(user), age, getUserCountry(user));
    
    freeUser(user);
}

// Função para a 2ª query sem especificação de país
void query2(int nArtists, GHashTable* artistTable, GHashTable* musicTable, FILE* output){
    
}

// Função para a 2ª query, com especificação de país
void query2b(int nArtists, char* country, GHashTable* artistTable, GHashTable* musicTable, FILE* output){

}

void query3(int ageMin, int ageMax, GHashTable* userTable, GHashTable* musicTable,FILE* output){

}

// Função que adiciona por ordem crescente de id de artista, um novo artista à lista ligada
Discography* artistInsert(Discography* disco, long int id, const char* name, const char* country, ArtistType type){
    
    // disco -> lista ligada recebida como argumento
    // newDisco -> lista para para guardar o novo artista
    // newHead -> auxiliar para percorrer a lista

    // Atribuição dos valores do novo artista a uma nova lista
    Discography* newDisco = (Discography*)malloc(sizeof(Discography));
    newDisco->id = id;
    newDisco->name = strdup(name);
    newDisco->country = strdup(country);
    newDisco->duration = 0; // Duração sempre 0
    newDisco->type = type;
    newDisco->next = NULL;

    // Caso o novo artista seja o 1º ou seja menor que o artista na cabeça da lista
    if (disco==NULL || id < disco->id) {
        newDisco->next = disco;
        return newDisco;
    }

    // Percorrer a lista até que o id do novo artista seja menor que a cabeça da lista
    Discography* newHead = disco;
    while (newHead->next && newHead->next->id < id) {
        newHead = newHead->next;
    }
    // O proximo id seria maior que o novo id, logo o novo id fica a apontar para esse proximo id
    newDisco->next = newHead->next;
    // A lista atual aponta para o novo id que tambem já aponta para um id maior (ordenado)
    newHead->next = newDisco;
    
    // Devolve a lista original com a lista do novo artista inserido ordenadamente
    return disco;
}

// Função para incrementar em segundos, a duração da discografia de um artista
void durationAdd(Discography* disco, const char* duration, long int id){
    
    // Converter a string de duração em segundos sem atoi
    int h=0, m=0, s=0;
    if (sscanf(duration, "%d:%d:%d", &h, &m, &s) != 3){
        // Em principio nunca acontece
        printf("Formato de duração inválido.\n");
        return;
    }

    int seconds = h*3600 + m*60 + s; // Calcula o total em segundos

    // Percorre a lista para encontrar o artista
    Discography* newDisco = disco;
    while (newDisco != NULL) {
        if (newDisco->id == id){
            newDisco->duration += seconds;
            break;
        }
        newDisco = newDisco->next; // Caso ainda não tenha encontrado o id respetivo
    }

    // Em principio nunca acontece
    printf("Artista com ID %ld não encontrado.\n", id);
}

// Função callback para cada item da Hash Table
/*void add_artist_to_discography(gpointer key, gpointer value, gpointer user_data) {
    Artist* artist = (Artist*)value;
    Discography** head = (Discography**)user_data;
    *head = insert_discography_ordered(*head, artist->id, artist->name, artist->country, artist->type);
}

// Função que percorre a Hash Table e insere cada artista na lista Discography
Discography* populateDiscographyList(GHashTable* table) {
    Discography* head = init_discography();
    g_hash_table_foreach(table, add_artist_to_discography, &head);
    return head;
}
*/