#include "../include/utils.h"

#define MAX_MUSICS 1000

//função responsável por remover as aspas.
char* remove_aspas(char* str) {
    if (!str) return NULL;  // Verifica se a string é nula

    char* result = strdup(str);
    if(!result){
        return NULL;
    }

    int len = strlen(result);
    if (len == 0) return result;  // Se a string for vazia, retorne-a diretamente

    // Se a string começa com aspas
    if(result[0] == '"'){
        memmove(result, result+1, len);
    }

    len = strlen(result);
    // Se a string acaba com aspas
    if(result[len - 1] == '"'){
        result[len - 1] = '\0';
    }

    return result;  // Retorna a string sem alterações se não houver aspas
}

// Função que remove espaços de uma dada string
char* remove_espacos(char* input){
    int i,j;
    char *output=input;
    int tam = strlen(input);
    for (i = 0, j = 0; i<tam; i++,j++){
        if (input[i]!=' ')                           
            output[j]=input[i];                     
        else
            j--;                                     
    }
    output[j]=0;
    return output;
}

// função que verifica se toda a string é composta por dígitos
int strDigit(char *str){

    if(!str){
        return 1;
    }

    for(int i=0;str[i]!='\0';i++){
        if(isdigit(str[i])==0){
            return 1;
        }
    }
    return 0;
}

// função para verificar se o nome é inteiramente carateres.
int nameVerify(char *name){
    
    // Caso vazio
    if(!name){
        return 1;
    }

    while(*name){
        if(!isalpha(*name)){
            return 1;
        }
        name++;
    }
    return 0;
}

// função que valida um endereço de email, dividindo por tokens e verificando se e qual o conteudo desses tokens.
int emailVerify(char *email){
    if(!email){
        return 1;
    }

    char *email_cpy = strdup(email);
    if(!email_cpy){
        perror("erro ao duplicar o email.\n");
        return 1;
    }

    char *original_cpy = email_cpy;

    // Testar com  casos práticos a divisao por tokens
    char *user = strsep(&email_cpy, "@");
    char *lDomain = strsep(&email_cpy, ".");
    char *rDomain = strsep(&email_cpy, "\0");

    if(!user || !lDomain || !rDomain){
        free(original_cpy);
        return 1;
    }

    if(strlen(user)<1){
        free(original_cpy);
        return 1;
    }

    for(int i=0;user[i]!='\0';i++){
        if(isdigit(user[i])==0 && isalpha(user[i])==0){
            free(original_cpy);
            return 1;
        }
    }

    if(nameVerify(lDomain) != 0 || strlen(lDomain)<1){
        free(original_cpy);
        return 1;
    }

    if(nameVerify(rDomain) != 0 || strlen(rDomain)<2 || strlen(rDomain)>3){
        free(original_cpy);
        return 1;
    }

    free(original_cpy);
    return 0;
}

// função que valida uma data de nascimento mediante os requerimentos.
int birthDateVerify(char* birth_date){
    // data base 2024/09/09

    if(!birth_date){
        return 1;
    }

    char* date_cpy = strdup(birth_date);
    if(!date_cpy){
        return 1;
    }

    char* original_cpy = date_cpy;

    if(date_cpy[4] != '/' || date_cpy[7] != '/' || date_cpy[10] != '\0'){
        free(original_cpy);
        return 1;
    }

    char *ano = strsep(&date_cpy, "/");
    char *mes = strsep(&date_cpy, "/");
    char *dia = strsep(&date_cpy, "\0");

    if(strDigit(ano)!=0 || strDigit(mes)!=0 || strDigit(dia)!=0){
        free(original_cpy);
        return 1;
    }

    // Data numérica verificada, transformar em int
    int anoInt = atoi(ano);
    int mesInt = atoi(mes);
    int diaInt = atoi(dia);

    // Verificação lógica
    if(anoInt>2024 || (anoInt==2024 && mesInt>9) || (anoInt==2024 && mesInt==9 && diaInt>9)){
        free(original_cpy);
        return 1;
    }
    else if(anoInt<0){
        free(original_cpy);
        return 1;
    }
    else if(mesInt<=0 || mesInt>12){
        free(original_cpy);
        return 1;
    }
    else if(diaInt<=0 || diaInt>31){
        free(original_cpy);
        return 1;
    }

    free(original_cpy);
    return 0;
}

// função que faz a validação sintática da duração de uma música.
int verify_duration(char* duration){
    // se cumpre o formato "hh:mm:ss"
    if (strlen(duration) != 8 && duration[2] != ':' && duration[5] != ':') {
        return 0; // invalid format
    }

    // verificar se as horas, minutos e segundos sao digitos entre 0 e 9
    for (int i = 0; i < 8; i++) {
        if (i != 2 && i != 5) { // nao interessa os ':'
            if (!isdigit(duration[i])) {
                return 0; 
            }
        }
    }

    // convertemos as horas, minutos e segundos a inteiros.
    int hours = (duration[0] - '0') * 10 + (duration[1] - '0'); 
    int minutes = (duration[3] - '0') * 10 + (duration[4] - '0');
    int seconds = (duration[6] - '0') * 10 + (duration[7] - '0');

    // verificamos se cumprem os intervalos estabelecidos 
    if (hours < 0 || hours > 100 || minutes < 0 || minutes > 60 || seconds < 0 || seconds > 60) {
        return 0;
    }

    return 1; 
}

// função que verifica se um dado ano é válido.
int verify_year(int year){
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    int currentYear = tm_info->tm_year + 1900;
    if (year > currentYear) return 0;

    return 1;
}

// função que calcula a idade através de uma data de nascimento dada como argumento.
int calculaIdade(char* birthdate){
    char* currentDate = "2024/09/09";
    int birthYear, birthMonth, birthDay, currentYear, currentMonth, currentDay;

    sscanf(birthdate, "%d/%d/%d", &birthYear, &birthMonth, &birthDay);
    sscanf(currentDate, "%d/%d/%d", &currentYear, &currentMonth, &currentDay);

    int age = currentYear - birthYear;

    if(currentMonth < birthMonth || (currentMonth == birthMonth && currentDay < birthDay)){
        age--;
    }

    return age;
}

// Função que faz a validação lógica dos id_constituent de um artista
int verifyConstituent(char* type, char* constituent){
    int len = strlen(constituent);
    // Se o nosso type for individual, o id_constituent tem que ser uma lista vazia []
    if(!strcmp(type,"individual")){
        if(len==2) return 1;
        else return 0;
    }
    return 1; // Como não é individual só pode ser group
}

// Função que verifica se o formato do ID é válido, i.e, tem que ser [ID]
int isFormatValid(const char *input){
    if (input[0] == '[' && input[strlen(input) - 1] == ']'){
        return 1;
    }
    return 0; 
}

// Função que dado um array de IDs converte de char para long int
long int* convertID(const char *input, int *count){
    // Verificar se tem um formato valido, pois existem entries sem []
    if (!isFormatValid(input)){
        *count = 0;
        return 0;
    }

    char *input_copy = strdup(input);
    char *input_copy_index=input_copy;
    // Remover os parentesis retos
    input_copy++;
    input_copy[strlen(input_copy) - 1] = '\0';

    // Verificar se está empty
    if(strlen(input_copy) == 0){
        *count = 0;
        free(input_copy_index);
        return 0;
    }

    // Contar o número de ids através das virgulas, o nosso contador começa 1, pois podemos ter um array de um só elemento
    *count = 1;
    for (char *c = input_copy; *c != '\0'; c++){
        if (*c == ',') (*count)++;
    }

    // Após a contagem, alocamos memoria para este novo array
    long int *convertedIDs = (long int*) malloc(*count * sizeof(long int));
    if (convertedIDs == NULL){
        perror("Erro ao alocar memoria para o array de IDs\n");
        free(input_copy); 
        exit(EXIT_FAILURE);
    }

    char *token;
    int index = 0;
    // Percorremos toda a linha até não encontrarmos uma virgula
    while ((token = strsep(&input_copy, ",")) != NULL){
        remove_espacos(token);
        // Remover as plicas
        if (token[0] == '\'' && token[strlen(token) - 1] == '\'' ){
            token++;
            token[strlen(token) - 1] = '\0'; 
        }

        // Convertemos o ID para um long int e damos store no array
        convertedIDs[index] = strtol(token + 1, NULL, 10); 
        index++;
    }

    free(input_copy_index);  // Libertamos a memoria do pointer original

    return convertedIDs;
}

// Função que remove new lines
void removeEnters(char *input){
    int len = strlen(input);
    len--;

    if(input[len]=='\n'){
        input[len]='\0';
    }
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

// Função que dado um genero, retorna a posição do genero no array
int getGenreIndex(char *genre, char **genre_array, int genre_count){
    for(int i = 0; i < genre_count; i++){
        if(strcmp(genre_array[i], genre) == 0){
            return i;
        }
    }
    return -1;
}

// Função que faz sorting do array de generos e o array de likes em função do maior numero de likes
void sortGenresByLikes(char* genres[], long int genre_likes[], int genre_count){
    for(int i=0;i<genre_count - 1;i++){
        for(int j = i+1;j<genre_count;j++){
            if (genre_likes[i] < genre_likes[j] || 
               (genre_likes[i] == genre_likes[j] && strcmp(genres[i], genres[j]) > 0)){ // Se tiver o mesmo num de likes prevalecer a ordem alfabética
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

// Função que verifica se uma dada idade está compreendida entre os intervalos de idades
int isAgeInRange(int age, int minAge, int maxAge){
    return age >= minAge && age <= maxAge;
}

// Função que dados novos arrays de generos e likes, atualiza o conteúdo dos arrays originais de generos e likes
void updateGenresAndLikes(
    char*** genres,       // Apontador do array de generos
    long int** likes,     // Apontador do array de likes
    int* size,            // Apontador para o tamanho dos arrays
    char** newGenres,     // Novo array de generos
    long int* newLikes,   // Novo array de likes
    int newSize           // Novo tamanho dos arrays
){
    for(int i = 0; i < newSize; i++){
        int found = 0;
        for(int j = 0; j < *size; j++){
            if(strcmp((*genres)[j], newGenres[i]) == 0){
                // Se o genero existir, atualizamos os likes
                (*likes)[j] += newLikes[i];
                found = 1;
                break;
            }
        }
        if(!found){
            // Neste caso o genero não existe, então adicionamos ao array de generos
            (*size)++;
            *genres = realloc(*genres, *size * sizeof(char*));
            *likes = realloc(*likes, *size * sizeof(long int));
            if(!*genres || !*likes){
                fprintf(stderr, "Memory allocation failed for genres or likes\n");
                return;
            }
            (*genres)[*size - 1] = strdup(newGenres[i]);
            (*likes)[*size - 1] = newLikes[i];
        }
    }
}

// Função que cria a diretoria "dataset-errors" e respetivos ficheiros com cabeçalhos
void errosDir(){
    FILE *errors;

    // Ficheiros de erros com respetivos cabeçalhos
    errors = fopen("resultados/users_errors.csv", "w");
    if(!errors){
        perror("Erro ao criar o ficheiro de erros de users.\n");
        exit(EXIT_FAILURE);
    }
    fprintf(errors, "\"username\";\"email\";\"first_name\";\"last_name\";\"birth_date\";\"country\";\"subscription_type\";\"liked_songs_id\"\n");
    fclose(errors);

    errors = fopen("resultados/artists_errors.csv", "w");
    if(!errors){
        perror("Erro ao criar o ficheiro de erros de artists.\n");
        exit(EXIT_FAILURE);
    }
    fprintf(errors, "\"id\";\"name\";\"description\";\"recipe_per_stream\";\"id_constituent\";\"country\";\"type\"\n");
    fclose(errors);

    errors = fopen("resultados/musics_errors.csv", "w");
    if(!errors){
        perror("Erro ao criar o ficheiro de erros de musics.\n");
        exit(EXIT_FAILURE);
    }
    fprintf(errors, "\"id\";\"title\";\"artist_id\";\"duration\";\"genre\";\"year\";\"lyrics\"\n");
    fclose(errors);
}

// Função que recebe uma linha e escreve no csv de erros
void writeErrors(char* line, int csvFile){
    FILE *errors;
    switch(csvFile){
        case 1:
            errors = fopen("resultados/artists_errors.csv", "a");
            if(!errors){
                perror("Erro ao escrever no ficheiro de erros de artists.\n");
                exit(EXIT_FAILURE);
            }
            fprintf(errors, "%s", line);
            fclose(errors);
            break;
        case 2:
            errors = fopen("resultados/musics_errors.csv", "a");
            if(!errors){
                perror("Erro ao escrever no ficheiro de erros de musics.\n");
                exit(EXIT_FAILURE);
            }
            fprintf(errors, "%s", line);
            fclose(errors);
            break;
        case 3:
            errors = fopen("resultados/users_errors.csv", "a");
            if(!errors){
                perror("Erro ao escrever no ficheiro de erros de users.\n");
                exit(EXIT_FAILURE);
            }
            fprintf(errors, "%s", line);
            fclose(errors);
            break;
    }
}