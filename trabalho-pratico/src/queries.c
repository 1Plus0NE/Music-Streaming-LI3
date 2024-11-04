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
        return;
    }

    int age = calculaIdade(getUserBirthDate(user));

    fprintf(output_file, "%s;%s;%s;%d;%s\n", getUserEmail(user), getUserFirstName(user), getUserLastName(user), age, getUserCountry(user));

    freeUser(user);
}

// Results é necessário para escrever pela ordem pedida
// Função para a query 2
void query2(int nArtists, Discography* disco, FILE* output) {
    Discography* head = disco;
    char** results = malloc(nArtists * sizeof(char*)); // Array para armazenar os resultados
    int count = 0; // Contador de artistas correspondentes

    // Armazenar os resultados
    while (head != NULL && count < nArtists) {
        char* time = secondsToString(head->duration); // Transformação em formato char*
        char* typeInChar = typeToString(head->type); // Transformação em formato char*

        // Formatar a string e armazenar no array
        int length = strlen(head->name) + strlen(typeInChar) + strlen(time) + strlen(head->country) + 4; // +4 para os delimitadores e o null terminator
        results[count] = malloc(length * sizeof(char));
        snprintf(results[count], length, "%s;%s;%s;%s", head->name, typeInChar, time, head->country);

        free(time);
        free(typeInChar);

        count++; // Incrementa o contador
        head = head->next; // Avança para o próximo nó
    }

    // Escrever no arquivo em ordem inversa
    for (int i = count - 1; i >= 0; i--) {
        fprintf(output, "%s\n", results[i]);
        free(results[i]); // Liberar a memória alocada para cada resultado
    }

    free(results); // Liberar o array de resultados
}

// Função para a query 2 com especificação do pais
// results é necessário para escrever pela ordem pedida
void query2b(int nArtists, char* country, Discography* disco, FILE* output) {
    Discography* head = disco;
    char** results = malloc(nArtists * sizeof(char*)); // Array para armazenar os resultados
    int count = 0; // Contador de artistas correspondentes

    // Armazenar os resultados
    while (head != NULL && count < nArtists) {
        if (strcmp(head->country, country) == 0) { // Verificação do país do artista
            char* time = secondsToString(head->duration); // Transformação em formato char*
            char* typeInChar = typeToString(head->type); // Transformação em formato char*

            // Formatar a string e armazenar no array
            int length = strlen(head->name) + strlen(typeInChar) + strlen(time) + strlen(head->country) + 4; // +4 para os delimitadores e o null terminator
            results[count] = malloc(length * sizeof(char));
            snprintf(results[count], length, "%s;%s;%s;%s", head->name, typeInChar, time, head->country);

            free(time);
            free(typeInChar);

            count++; // Incrementa o contador
        }
        head = head->next; // Avança para o próximo nó
    }

    // Escrever no arquivo em ordem inversa
    for (int i = count - 1; i >= 0; i--) {
        fprintf(output, "%s\n", results[i]);
        free(results[i]); // Liberar a memória alocada para cada resultado
    }
    
    free(results); // Liberar o array de resultados
}

void query3(int ageMin, int ageMax, GHashTable* userTable, GHashTable* musicTable, FILE* output){

}

//----------------Funções referentes à discografia------------------

// Função que adiciona artista por artista numa lista ligada, ignorando a ordem 
void artistInsert(Discography** disco, long int id, const char* name, const char* country, ArtistType type){
    // Atribuição dos valores do novo artista a uma nova lista
    Discography* newDisco = (Discography*)malloc(sizeof(Discography));
    if (!newDisco) {
        perror("Erro ao alocar memória para o novo artista.\n");
        exit(EXIT_FAILURE);
    }
    newDisco->id = id;
    newDisco->name = strdup(name);
    newDisco->country = strdup(country);
    newDisco->duration = 0; // Duração sempre 0
    newDisco->type = type;
    newDisco->next = *disco;
    
    *disco = newDisco; // Atualização da lista
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

    // Em principio nunca acontece, não é suposto se os dados são validos
    if(newDisco == NULL) printf("Artista com ID %ld não encontrado.\n", id);
}

void freeDiscography(Discography* disco) {
    Discography* currentDisco = disco;
    Discography* nextDisco;

    while (currentDisco != NULL) {
        nextDisco = currentDisco->next;
        free(currentDisco->name);
        free(currentDisco->country);
        free(currentDisco);
        currentDisco = nextDisco;
    }
}

// Função que percorre a Hash Table e insere cada artista na lista Discography
Discography* fillWithArtists(GHashTable* table, Discography* disco){

    g_hash_table_foreach(table, artistFromTableToLL, &disco);
    return disco;
}

// Função  para cada item da Hash Table
void artistFromTableToLL(gpointer _artistId, gpointer artistData, gpointer discoPtr){
    
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
}

// Função principal para percorrer a hash table e atualizar as durações dos artistas
Discography* updateArtistsDurationFromMusic(GHashTable* musicTable, Discography* disco){

    g_hash_table_foreach(musicTable, artistDurationAdd, &disco);
    return disco;
}

// Função para processar cada música e atualizar a duração nos artistas correspondentes
void artistDurationAdd(gpointer _musicId, gpointer musicData, gpointer discoPtr){
   
    //Music* music = (Music*)musicData;
    Discography* disco = *((Discography**)discoPtr);
    int numArtists = getMusicNumArtists(musicData);
    char* duration = getMusicDuration(musicData);
    long int* musicArtistsId = getMusicArtistIDs(musicData);
    
    for(int i=0; i<numArtists; i++){
        durationAdd(disco, duration, musicArtistsId[i]);
    }

    free(duration);
    free(musicArtistsId);
}

// Função para ordenar a discografia por durações
void sortByDuration(Discography** head){
    if (*head == NULL || (*head)->next == NULL) {
        // Lista vazia ou com um único elemento não precisa de ordenação
        return;
    }

    int swapped;
    Discography *ptr1;
    Discography *lptr = NULL;

    do {
        swapped = 0;
        ptr1 = *head;

        while (ptr1->next != lptr) {
            if (ptr1->duration > ptr1->next->duration) {
                // Trocar os dados dos artistas
                long int tempId = ptr1->id;
                char* tempName = ptr1->name;
                char* tempCountry = ptr1->country;
                int tempDuration = ptr1->duration;
                ArtistType tempType = ptr1->type;

                ptr1->id = ptr1->next->id;
                ptr1->name = ptr1->next->name;
                ptr1->country = ptr1->next->country;
                ptr1->duration = ptr1->next->duration;
                ptr1->type = ptr1->next->type;

                ptr1->next->id = tempId;
                ptr1->next->name = tempName;
                ptr1->next->country = tempCountry;
                ptr1->next->duration = tempDuration;
                ptr1->next->type = tempType;

                swapped = 1; // Indica que uma troca ocorreu
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1; // O último elemento já está ordenado
    } while (swapped);
}

// Função para voltar a transformar o total de segundos na discografia no formato "hh:mm:ss"
char* secondsToString(int totSeconds){

    int hours = totSeconds / 3600;
    int minutes = (totSeconds % 3600) / 60;
    int seconds = (totSeconds % 3600) % 60;

    // Aloca memória para a string de resultado
    char* timeString = (char*)malloc(9 * sizeof(char)); // "hh:mm:ss" + '\0' = 9 caracteres
    if (!timeString) {
        perror("Erro ao alocar memória para timeString");
        exit(EXIT_FAILURE);
    }

    // Formata a string como "hh:mm:ss"
    snprintf(timeString, 9, "%02d:%02d:%02d", hours, minutes, seconds);

    return timeString;
}