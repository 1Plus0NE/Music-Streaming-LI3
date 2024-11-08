#include "../include/queries.h"
#define MAX_GENRES 10

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
    char* email = getUserEmail(user);
    char* first_name = getUserFirstName(user);
    char* last_name = getUserLastName(user);
    char* age_str = getUserBirthDate(user);
    int age = calculaIdade(age_str);
    char* country = getUserCountry(user);

    fprintf(output_file, "%s;%s;%s;%d;%s\n", email, first_name, last_name, age, country);
    free(email);
    free(first_name);
    free(last_name);
    free(age_str);
    free(country);
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


// Função que Dado um user, verifica se está compreendido entre os intervalos de idades
int isUserInRange(User *user, int minAge, int maxAge){
    char* tmp_userAge = getUserBirthDate(user);
    int userAge = calculaIdade(tmp_userAge);
    free(tmp_userAge);
    return userAge >= minAge && userAge <= maxAge;
}

// Função que dado um genero, retorna a posição do genero no array
int getGenreIndex(char *genre, char **genre_array, int genre_count){
    for(int i = 0; i < genre_count; i++){
        if(strcmp(genre_array[i], genre) == 0){
            return i;
        }
    }
    return -1;
}

// Função responsável por popular o array de generos e contar o numero total de likes no array de likes
void countUserLikedMusics(User* user, GestorMusic* gestorMusic, char* genres[], long int genre_likes[], int* genre_count){
    long int* likedMusics = getUserLikedMusics(user);
    int numLikedMusics = getUserNumLikedMusics(user);
    Music* music = NULL;
    char* genre;
    int index;

    for(int i=0;i<numLikedMusics;i++){
        music = searchMusic(gestorMusic, likedMusics[i]);

        if(music != NULL){ // em principio nunca falha porque as liked musics do user ja sao verificadas no parsing 
            genre = getMusicGenre(music);
            index = getGenreIndex(genre, genres, *genre_count);

            if(index == -1 && *genre_count < MAX_GENRES){
                genres[*genre_count] = strdup(genre);
                genre_likes[*genre_count] = 1;
                (*genre_count)++;
            }
            else genre_likes[index]++;  
            free(genre);
        }
    }
    free(likedMusics); // Free do array de liked musics do user 
}

// Função que faz sorting do array de generos e o array de likes em função do maior numero de likes
void sortGenresByLikes(char* genres[], long int genre_likes[], int genre_count){
    for(int i=0;i<genre_count - 1;i++){
        for(int j = i+1;j<genre_count;j++){
            if(genre_likes[i] < genre_likes[j]){
                // Swap generos
                char* temp_genre = genres[i];
                genres[i] = genres[j];
                genres[j] = temp_genre;

                // Swap likes
                long int temp_likes = genre_likes[i];
                genre_likes[i] = genre_likes[j];
                genre_likes[j] = temp_likes;
            }
        }
    }
}

// Função responsável da query 3
void query3(int ageMin, int ageMax, GHashTable* userTable, GestorMusic* gestorMusic, FILE* output){
    
    if(ageMin == 100 || ageMax == 0){
        fprintf(output, "\n");
        return;
    }

    // Para iterar os users
    GHashTableIter user_iter;
    gpointer user_key, user_value;
    User* user = NULL;
    // Variaveis para dar store aos valores
    char *genres[MAX_GENRES];
    long int genre_likes[MAX_GENRES] = {0};
    int genre_count = 0;

    // Flag para caso os intervalos de idades sejam validos mas não haja users compreendidos nessas idades
    int flag = 0;

    // Iterar pela table de users
    g_hash_table_iter_init(&user_iter, userTable);
    while (g_hash_table_iter_next(&user_iter, &user_key, &user_value)){
        user = (User *)user_value;
        if(isUserInRange(user, ageMin, ageMax)){
            flag = 1;
            countUserLikedMusics(user, gestorMusic, genres, genre_likes, &genre_count);
        }
    }

    // No caso de nao termos encontrado um user na range de idades
    if(!flag){
        fprintf(output, "\n");
        return;
    }

    sortGenresByLikes(genres, genre_likes, genre_count);
    // Escrever no ficheiro o resultado final
    for(int i = 0; i < MAX_GENRES; i++){
        fprintf(output, "%s;%ld\n", genres[i], genre_likes[i]);  
        if(genres[i])free(genres[i]);
    }

}