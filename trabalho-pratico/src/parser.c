#include "../include/parser.h"

// Função que cria a diretoria "dataset-errors" e respetivos ficheiros com cabeçalhos
    // Possivelmente inutil, mudar módulo posteriormente
    // se calhar nao é necessário criar a dir
void errorsDir(){
    // Criação da diretoria
    if (mkdir("../resultados", 0777) == -1) {
        if (errno == EEXIST) printf("Diretoria já existente.\n");
        else {
            perror("Erro ao criar a diretoria.\n");
            exit(EXIT_FAILURE);
        }
    }
    else printf("resultados criado com sucesso.\n");

    // Ficheiros de erros com respetivos cabeçalhos
    FILE *errors = fopen("../resultados/users.csv", "w");
    if(!errors){
        perror("Erro ao criar o ficheiro de erros de users.\n");
        exit(EXIT_FAILURE);
    }
    fprintf(errors, "\"username\";\"email\";\"first_name\";\"last_name\";\"birth_date\";\"country\";\"subscription_type\";\"liked_songs_id\"\n");
    fclose(errors);

    fopen("../resultados/artists.csv", "w");
    if(!errors){
        perror("Erro ao criar o ficheiro de erros de artists.\n");
        exit(EXIT_FAILURE);
    }
    fprintf(errors, "\"id\";\"name\";\"description\";\"recipe_per_stream\";\"id_constituent\";\"country\";\"type\"\n");
    fclose(errors);

    fopen("../resultados/musics.csv", "w");
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
            errors = fopen("../resultados/artists.csv", "a");
            if(!errors){
                perror("Erro ao escrever no ficheiro de erros de artists.\n");
                exit(EXIT_FAILURE);
            }
            fprintf(errors, "%s", line);
            fclose(errors);
            break;
        case 2:
            errors = fopen("../resultados/musics.csv", "a");
            if(!errors){
                perror("Erro ao escrever no ficheiro de erros de musics.\n");
                exit(EXIT_FAILURE);
            }
            fprintf(errors, "%s", line);
            fclose(errors);
            break;
        case 3:
            errors = fopen("../resultados/users.csv", "a");
            if(!errors){
                perror("Erro ao escrever no ficheiro de erros de users.\n");
                exit(EXIT_FAILURE);
            }
            fprintf(errors, "%s", line);
            fclose(errors);
            break;
        default:
            printf("Opcao invalida.\n");
    }
}

// função para ler e fazer parse de um ficheiro CSV de artistas.
void parse_artist(char* path){
    //variáveis para o parse
    FILE* artists;
    char filename[1024];
    char line[2048];
    char original_line[2048];
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
    char* type;

    snprintf(filename,1024,"%s/artists.csv", path);

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
        type = remove_aspas(strsep(&tmp_line,";"));
        removeEnters(description);

        if(isFormatValid(id_constituent)){
            id_constituent_converted = convertID(id_constituent, &num_constituent);
            Artist* a = createArtist(id, name, description, recipe_per_stream, id_constituent_converted, num_constituent, country, type);
            // adiciona à tabela de artists
            free(id_constituent_converted);
        }
       
        else{
            writeErrors(original_line, 1);
        }   

    }
    fclose(artists);
}

// Função para ler e fazer parse de um ficheiro CSV de músicas.
void parse_musics(char* path){
    // Variaveis para o parse 
    FILE* musics;
    char filename[1024];
    char line[2048];
    char original_line[2048];
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

    // music_table = createMusicTable(); // criar a tabela de musicas
    snprintf(filename,1024,"%s/musics.csv",path); //abrir ficheiro de musicas

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
        
        if(isFormatValid(artist_id) && verify_year(year) && verify_duration(duration)){
            artist_id_converted = convertID(artist_id, &num_artists); // daqui temos o array de ids de artistas + o num_artists calculado
            Music* m = createMusic(id, title, artist_id_converted, num_artists, duration, genre, year, lyrics);
            //addMusic(music_table, m);
            free(artist_id_converted);
        }
       
        else{
            writeErrors(original_line, 2);
        }   

    }
    fclose(musics);
}

// função para ler e fazer parse de um ficheiro CSV de artistas.
void parse_user(char* path){
    //variáveis para o parse
    FILE* users;
    char filename[1024];
    char line[2048];
    char original_line[2048];
    char *tmp_line=NULL;

    //argumentos para a struct de artistas
    char *username;
    char* email;
    char* first_name;
    char* last_name;
    char birth_date[10];
    char* country;
    char subscription_type[7];
    //char* liked_musics_id;
    long int* liked_musics_id_converted;
    int num_liked_musics=0;

    snprintf(filename,1024,"%s/users.csv", path);

    users = fopen(filename, "r");
    if(!users){
        perror("Erro ao abrir o ficheiro csv dos utilizadores.\n");
        exit(EXIT_FAILURE);
    }

    fgets(line, sizeof(line), users);

    while((fgets(line, sizeof(line), users) != NULL)){
        strcpy(original_line, line);
        tmp_line = line;

        // Antes da função atribuir valor as variaveis, verifica a sua validação
        // tmp_line sera alterada na verificaçao
        // line sera alterada na atribuição
        // original_line permanece intacta, para erro
        if(userLineVerify(tmp_line) == 0){
            username = remove_aspas(strsep(&line, ";"));
            email = remove_aspas(strsep(&line, ";"));
            first_name = remove_aspas(strsep(&line,";"));
            last_name = remove_aspas(strsep(&line,";"));
            strncpy(birth_date, remove_aspas(strsep(&line, ";")), sizeof(birth_date) - 1);
            birth_date[10] = '\0';
            country = remove_aspas(strsep(&line,";"));
            strncpy(subscription_type, remove_aspas(strsep(&line, ";")), sizeof(subscription_type) - 1);
            subscription_type[7] = '\0';
            //subscription_type = remove_aspas(strsep(&line,";"));
            liked_musics_id_converted = convertID(remove_aspas(strsep(&line,"\n")), &num_liked_musics);

            User* u = createUser(username, email, first_name, last_name, birth_date, country, subscription_type, liked_musics_id_converted, num_liked_musics);
            //liked_musics_id = remove_aspas(strsep(&line,"\n"));

        // parsed++;
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
            //erros++;
            writeErrors(original_line, 3);
        }   
    }
    // printf("Foram lidos %d dados, foram validados %d dados e foram encontrados %d erros.\n", parsed, verified, erros);

    fclose(users);
}

//Função responsável por ler e fazer parse de um arquivo CSV de users.
/*int parse_user_csv(const char *filename){
    
    FILE *user = fopen(filename, "r");
    if(!user){
        perror("Erro a abrir o ficheiro de users.\n");
        exit(EXIT_FAILURE);
    }

    FILE *usersErrors = fopen("../../dataset-errors/users.csv", "a");
    if(!usersErrors){
        perror("Erro a abrir o ficheiro de erros de users.\n");
        exit(EXIT_FAILURE);
    }

    char *line = malloc(sizeof(char)*1500);
    char *dupLine = NULL;
    // Ignora a 1ª linha do ficheiro
    fgets(line, 90, user);

    while(fgets(line, 1500, user)){

        dupLine = malloc(sizeof(char)*1500);
        dupLine = strdup(line);
        if(userLineVerify(dupLine) == 0){
            
            char *username; 
            char *email;
            char *first_name;
            char *last_name;
            char *birth_date[10];
            char *country;
            char *subscription_type[7];
            long int *liked_musics_id;
            int num_liked_musics = 0;
            //int *liked_musics_id = NULL;
            // int num_liked_musics = 0;
        
            // char* token = strsep(&line, "\n");
            char *info = strsep(&line, ";");

            for(int i = 0; i <= 7; i++){

                if(info){
                    switch(i){
                        case 0:
                            strcpy(username, remove_aspas(info));
                            info = strsep(&line, ";");
                            break;
                        case 1:
                            strcpy(email, remove_aspas(info));
                            info = strsep(&line, ";");
                            break;
                        case 2:
                            strcpy(first_name, remove_aspas(info));
                            info = strsep(&line, ";");
                            break;
                        case 3:
                            strcpy(last_name, remove_aspas(info));
                            info = strsep(&line, ";");
                            break;
                        case 4:
                            strcpy(birth_date, remove_aspas(info));
                            info = strsep(&line, ";");
                            break;
                        case 5:
                            strcpy(country, remove_aspas(info));
                            info = strsep(&line, ";");
                            break;
                        case 6:
                            strcpy(subscription_type, remove_aspas(info));
                            info = strsep(&line, "\n");
                            break;
                        case 7:
                            // liked_musics_id
                            // num_liked_musics=?
                            break;
                        default:
                            break;
                    }
                }
            }
        //free(*char); ??
        //User* user = createUser(username, email, first_name, last_name, birth_date , genre, country, subscription_type, liked_musics_id, num_liked_musics);
        //freeUser(user);
        //local onde depois será feita o armazenamento na hashtable(estrutura de dados) 
        }
        else{
            fputs(line, usersErrors);
        }
        free(dupLine); //?? Mem leak?
    }
    
    fclose(user);
    fclose(usersErrors);
    free(dupLine);
    free(line);
    return 0;
}*/
// Verificar/Corrigir os apontadores e os endereços nas chamadas de funções.