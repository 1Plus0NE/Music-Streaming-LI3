#include "../include/parser.h"
#define MAX_FILENAME 1024
#define MAX_LINE 2048

// Função que cria a diretoria "dataset-errors" e respetivos ficheiros com cabeçalhos
    // Possivelmente inutil, mudar módulo posteriormente
    // se calhar nao é necessário criar a dir
void errosDir(){
     FILE *errors;
    // Criação da diretoria
    if (mkdir("resultados", 0777) == -1) {
        if (errno == EEXIST) printf("Diretoria já existente.\n");
        else {
            perror("Erro ao criar a diretoria.\n");
            exit(EXIT_FAILURE);
        }
    }
    else printf("resultados criado com sucesso.\n");

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

// função para ler e fazer parse de um ficheiro CSV de artistas.
void parse_artist(char* path, GHashTable* artist_table){
    //variáveis para o parse
    FILE* artists;
    char filename[MAX_FILENAME];
    char line[MAX_LINE];
    char original_line[MAX_LINE];
    char *tmp_line=NULL;

    //argumentos para a struct de artistas
    char *id_str;
    long int id;
    char* name;
    char* description;
    float recipe_per_stream;
    char* id_constituent;
    long int* id_constituent_converted;
    int num_constituent;
    char* country;
    char* type_str;
    ArtistType type;

    snprintf(filename,MAX_FILENAME,"%s/artists.csv", path);

    artists = fopen(filename, "r");
    if(!artists){
        perror("Erro ao abrir o ficheiro csv dos artistas.\n");
        exit(EXIT_FAILURE);
    }

    fgets(line, sizeof(line), artists);
    
    while((fgets(line, sizeof(line), artists) != NULL)){
        strcpy(original_line, line);
        tmp_line = line;

        id_str = remove_aspas(strsep(&tmp_line, ";"));
        id = strtol(id_str + 1, NULL, 10);
        name = remove_aspas(strsep(&tmp_line,";"));
        description = remove_aspas(strsep(&tmp_line,";"));
        recipe_per_stream = atof(remove_aspas(strsep(&tmp_line,";")));
        id_constituent = remove_aspas(strsep(&tmp_line,";"));
        country = remove_aspas(strsep(&tmp_line,";"));
        type_str = remove_aspas(strsep(&tmp_line,";"));
        removeEnters(type_str);
        remove_aspas(type_str);
        //type = stringToArtistType(type_str); -> quero verificar primeiro se o field é válido

        if(isFormatValid(id_constituent) && verifyConstituent(type_str,id_constituent)){
            type = stringToArtistType(type_str);
            id_constituent_converted = convertID(id_constituent, &num_constituent);
            Artist* a = createArtist(id, name, description, recipe_per_stream, id_constituent_converted, num_constituent, country, type);
            addArtist(artist_table,a);
            free(id_constituent_converted);
        }
       
        else{
            writeErrors(original_line, 1);
        }   

    }
    fclose(artists);
}

// Função para ler e fazer parse de um ficheiro CSV de músicas.
void parse_music(char* path, GHashTable* music_table, GHashTable* artist_table){
    // Variaveis para o parse 
    FILE* musics;
    char filename[MAX_FILENAME];
    char line[MAX_LINE];
    char original_line[MAX_LINE];
    char *tmp_line=NULL;

    // Argumentos para a struct de musicas
    char *id_str; // para depois passar para long int
    long int id;
    char* title;
    char* artist_id; // para depois converter para um array de long ints
    long int* artist_id_converted;
    int num_artists;
    char* duration;
    char* genre;
    int year;
    char* lyrics;
    
    int erros = 0;

    snprintf(filename,MAX_FILENAME,"%s/musics.csv",path); //abrir ficheiro de musicas

    musics = fopen(filename, "r");
    if(!musics){
        perror("Erro ao abrir o ficheiro csv das musicas.\n");
        exit(EXIT_FAILURE);
    }

    fgets(line, sizeof(line), musics); //skip da primeira linha por ser o header

    while((fgets(line, sizeof(line), musics) != NULL)){
        strcpy(original_line, line);
        tmp_line = line;

        id_str = remove_aspas(strsep(&tmp_line, ";"));
        id = strtol(id_str + 1, NULL, 10);
        title  = remove_aspas(strsep(&tmp_line,";"));
        artist_id  = remove_aspas(strsep(&tmp_line,";"));
        duration  = remove_aspas(strsep(&tmp_line,";"));
        genre  = remove_aspas(strsep(&tmp_line,";"));
        year = atoi(remove_aspas(strsep(&tmp_line,";")));
        lyrics = remove_aspas(strsep(&tmp_line,";")); //as lyrics tem o \n lá porque é onde ha mudanca de linha
        removeEnters(lyrics);
        remove_aspas(lyrics);
        if(isFormatValid(artist_id) && verify_year(year) && verify_duration(duration)){
            artist_id_converted = convertID(artist_id, &num_artists); // daqui temos o array de ids de artistas + o num_artists calculado
            if(validateArtistIDs(artist_table, artist_id_converted ,num_artists)){
                    Music* m = createMusic(id, title, artist_id_converted, num_artists, duration, genre, year, lyrics);
                    addMusic(music_table, m);
                    free(artist_id_converted);
            }
            else{
                //erros++;
                writeErrors(original_line, 2);
            }         
        }
       
        else{
            erros++;
            writeErrors(original_line, 2);
        }   

    }
    printf("Foram encontrados %d erros",erros);
    fclose(musics);
}

// função para ler e fazer parse de um ficheiro CSV de artistas.
void parse_user(char* path/*,music_table,user_table*/){
    //variáveis para o parse
    FILE* users;
    char filename[MAX_FILENAME];
    char line[MAX_LINE];
    char original_line[MAX_LINE];
    char *tmp_oriLine=NULL;

    //argumentos para a struct de artistas
    char *username;
    char* email;
    char* first_name;
    char* last_name;
    char birth_date[10];
    char* country;
    SubscriptionType subscription;
    //char subscription_type[7];
    //char* liked_musics_id;
    long int* liked_musics_id_converted;
    int num_liked_musics=0;

    int parsed = 0;
    int erros = 0;

    snprintf(filename,MAX_FILENAME,"%s/users.csv", path);

    users = fopen(filename, "r");
    if(!users){
        perror("Erro ao abrir o ficheiro csv dos utilizadores.\n");
        exit(EXIT_FAILURE);
    }

    fgets(line, sizeof(line), users);

    while((fgets(line, sizeof(line), users) != NULL)){
        strcpy(original_line, line);
        //Apontadores para o strsep
        tmp_oriLine = original_line;

        // Antes da função atribuir valor as variaveis, verifica a sua validação
        // line para analise
        // original_line para escrita de resultado
        if(userLineVerify(line/*,musictable*/) == 0){
            username = remove_aspas(strsep(&tmp_oriLine, ";"));
            email = remove_aspas(strsep(&tmp_oriLine, ";"));
            first_name = remove_aspas(strsep(&tmp_oriLine,";"));
            last_name = remove_aspas(strsep(&tmp_oriLine,";"));
            strncpy(birth_date, remove_aspas(strsep(&tmp_oriLine, ";")), sizeof(birth_date) - 1);
            birth_date[10] = '\0';
            country = remove_aspas(strsep(&tmp_oriLine,";"));
            char* tmpSub = remove_aspas(strsep(&tmp_oriLine,";"));
            subscription = stringToSubscriptionType(tmpSub);
            //strncpy(subscription_type, remove_aspas(strsep(&tmp_oriLine, ";")), sizeof(subscription_type) - 1);
            //subscription_type[7] = '\0';
            //subscription_type = remove_aspas(strsep(&line,";"));
            liked_musics_id_converted = convertID(remove_aspas(strsep(&tmp_oriLine,"\n")), &num_liked_musics);

            User* u = createUser(username, email, first_name, last_name, birth_date, country, subscription, liked_musics_id_converted, num_liked_musics);
            //addUser(User_table, u);
            //free(liked_musics_id_converted);
            //liked_musics_id = remove_aspas(strsep(&line,"\n"));

            parsed++;
        // printf("ID: %li | Lyrics: %s \n",id,lyrics);
        }/*
        if(isFormatValid(liked_musics_id) && birthDateVerify(birth_date)){
            // verified++;
            liked_musics_id_converted = convertID(liked_musics_id, &num_liked_musics);
            User* u = createUser(username, email, first_name, last_name, birth_date, country, subscription_type, liked_musics_id_converted, num_liked_musics);
            // addMusic(music_table, m);
            // chama func para escrever no csv a linha (quando esta correta)
            free(liked_musics_id_converted);
        }*/

        else{
            erros++;
            writeErrors(original_line, 3); // Basta line?
        }   
    }
    printf("Foram lidos %d dados e foram encontrados %d erros.\n", parsed, erros);

    fclose(users);
}