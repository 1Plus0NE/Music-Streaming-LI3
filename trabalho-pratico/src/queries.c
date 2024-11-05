#include "../include/queries.h"
#define MAX_GENRES 11

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
void query2(int nArtists, Discography* disco, FILE* output){
    Discography* head = disco;

    if(nArtists == 0) fprintf(output, "\n"); // Caso de ficheiro "vazio"
    for(int i=0; i<nArtists && head!=NULL; i++){
        char* time = secondsToString(head->duration); // Transformação em formato char*
        char* typeInChar = typeToString(head->type); // Transformação em formato char*
        
        fprintf(output, "%s;%s;%s;%s\n", head->name, typeInChar, time, head->country);  
        
        free(time);
        free(typeInChar);

        head = head->next;
    }
}

// Função para a query 2 com especificação do pais
void query2b(int nArtists, char* country, Discography* disco, FILE* output){
    Discography* head = disco;

    if(nArtists == 0) fprintf(output, "\n"); // Caso de ficheiro "vazio"
    for(int i=0; i<nArtists && head!=NULL; i++){
        if(strcmp(head->country, country) == 0){ // Verificação do país do artista
            char* time = secondsToString(head->duration); // Transformação em formato char*
            char* typeInChar = typeToString(head->type); // Transformação em formato char*
        
            fprintf(output, "%s;%s;%s;%s\n", head->name, typeInChar, time, head->country);  
        
            free(time);
            free(typeInChar);

            head = head->next; 
        }
        else if(head->next == NULL && i==0){ // Caso de ficheiro "vazio"
            fprintf(output, "\n");
            head = head->next;
            i--; // Mantém o contador para processar o próximo artista
        }
        else{
            head = head->next;
            i--; // Mantém o contador para processar o próximo artista
        }
    }
}

int isUserInRange(User *user, int minAge, int maxAge){
    int userAge = calculaIdade(getUserBirthDate(user));
    return userAge > minAge && userAge < maxAge;
}

int getGenreIndex(char *genre, char **genre_array, int genre_count){
    for(int i = 0; i < genre_count; i++){
        if(strcmp(genre_array[i], genre) == 0){
            return i;
        }
    }
    return -1;
}

void query3(int ageMin, int ageMax, GHashTable* userTable, GHashTable* musicTable, FILE* output){

    fprintf(output, "\n");

}

/*
void query3(int ageMin, int ageMax, GHashTable* userTable, GHashTable* musicTable, FILE* output){
    
    if (ageMin == 100 || ageMax == 0){
        fprintf(output, "\n");
        return;
    }

    // Para iterar os users
    GHashTableIter user_iter;
    gpointer user_key, user_value;

    // Info do user
    User* user = NULL;
    long int *likedMusics = NULL;
    int numLikedMusics = 0;

    // Info da musica
    Music* music = NULL;
    long int musicID = 0;

    // Variaveis para dar store aos valores
    char *genres[MAX_GENRES];
    long int genre_likes[MAX_GENRES] = {0};
    int genre_count = 0;
    int index = 0;
    char* genre;

    // Flag para caso os intervalos de idades sejam validos mas não haja users compreendidos nessas idades
    int flag = 0;

    // Iterar pela table de users
    g_hash_table_iter_init(&user_iter, userTable);
    while (g_hash_table_iter_next(&user_iter, &user_key, &user_value)){
        user = (User *)user_value;

        if(isUserInRange(user, ageMin, ageMax)){
            flag = 1;
            likedMusics = getUserLikedMusics(user);
            numLikedMusics = getUserNumLikedMusics(user);

            // Para cada id de musicas com likes do user vamos contar para cada genero
            for(int i = 0; i < numLikedMusics; i++){
                musicID = likedMusics[i];
                music = searchMusic(musicTable, musicID);

                if(music != NULL){ // em principio nunca é null
                    genre = getMusicGenre(music); // para construir o array de generos 
                    index = getGenreIndex(genre, genres, genre_count); // para construir o array de likes
                    
                    if(index == -1){
                        // Caso de um genero novo e temos que adicionar ao array
                        if(genre_count < MAX_GENRES){
                            genres[genre_count] = genre;
                            genre_likes[genre_count] = 1;
                            genre_count++;
                        }
                    }
                    else{
                        // Caso o genero ja exista, é porque deu match e entao incrementamos o valor de likes para esse genero
                        genre_likes[index]++;
                    }
                }
            }
            
            free(likedMusics);
        }
    }

    // No caso de nao termos encontrado um user na range de idades
    if(!flag){
        fprintf(output, "\n");
        return;
    }

    // Ordenar os arrays de generos e likes respetivos
    for(int i = 0; i < genre_count - 1; i++){
        for(int j = i + 1; j < genre_count; j++){
            if(genre_likes[i] < genre_likes[j]){
                // Swap de generos
                char *temp_genre = genres[i];
                genres[i] = genres[j];
                genres[j] = temp_genre;

                // Swap de likes
                long int temp_likes = genre_likes[i];
                genre_likes[i] = genre_likes[j];
                genre_likes[j] = temp_likes;
            }
        }
    }

    // Escrever no ficheiro o resultado final
    for(int i = 0; i < genre_count; i++){
        fprintf(output, "%s;%ld\n", genres[i], genre_likes[i]);  
        free(genres[i]);
    }

}
*/

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

void freeDiscography(Discography* disco){
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
}

// Função principal para percorrer a hash table e atualizar as durações dos artistas
Discography* updateArtistsDurationFromMusic(GHashTable* musicTable, Discography* disco){

    g_hash_table_foreach(musicTable, artistDurationAdd, &disco);
    return disco;
}

// Função para processar cada música e atualizar a duração nos artistas correspondentes
void artistDurationAdd(G_GNUC_UNUSED gpointer musicId, gpointer musicData, gpointer discoPtr){
   
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
    if(*head == NULL || (*head)->next == NULL){
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
            // Mudança na condição de comparação para ordem decrescente
            if (ptr1->duration < ptr1->next->duration) {
                // Trocar os dados dos artistas
                long int tempId = ptr1->id;
                char* tempName = ptr1->name;
                char* tempCountry = ptr1->country;
                int tempDuration = ptr1->duration;
                ArtistType tempType = ptr1->type;

                // Efetua a troca
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