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

// Função para ler e fazer parse de um arquivo CSV de artistas.
int parse_artist_csv(const char* filename) {
    FILE* file = fopen(filename, "r");

    if(!file){
        perror("Erro ao abrir o arquivo csv dos artistas.\n");
        exit(EXIT_FAILURE);
    }

    char* line;

    fgets(line, sizeof(line), file);

    //char* errorsArtists = "../dataset-errors/artists.csv";

    while(fgets(line, sizeof(line), file)){
        int id;
        char* name = NULL;
        char* description = NULL;
        float recipe_per_stream;
        int constituents[10];
        int num_constituents = 0;
        char* country = NULL;
        char* type = NULL;

        char* token = strsep(&line, "\n");
        char* campo;

        for(int i = 0; i <= 8; i++){
            campo = strsep(&token, ";");

            if(campo){
                switch(i){
                    case 0:
                        id = atoi(remove_aspas(campo));
                        break;
                    case 1:
                        name = remove_aspas(campo);
                        break;
                    case 2:
                        description = remove_aspas(campo);
                        break;
                    case 3:
                        recipe_per_stream = atof(remove_aspas(campo));
                        break;
                    case 4:
                        while(campo && num_constituents < 10){
                            constituents[num_constituents++] = atoi(remove_aspas(campo));
                            campo = strsep(&token, ";");
                        }
                        break;
                    case 5:
                        country = remove_aspas(campo);
                        break;
                    case 6:
                        type = remove_aspas(campo);
                        break;
                    default:
                        break;
                }
            }
        }
        
        Artist* a = createArtist(id, name, description, recipe_per_stream, constituents, num_constituents, country, type);

        //local onde depois será feita o armazenamento na hashtable(estrutura de dados)

        freeArtist(a);
    }
    fclose(file);
    return 0;
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
    
    // int parsed=0; 
    // int verified=0;
    // int erros=0;

    // music_table = createMusicTable(); // criar a tabela de musicas
    snprintf(filename,1024,"%s/musics.csv",path); //abrir ficheiro de musicas

    musics = fopen(filename, "r");
    if(!musics){
        perror("Erro ao abrir o ficheiro csv das musicas.\n");
        exit(EXIT_FAILURE);
    }

    fgets(line, sizeof(line), musics); //skip da primeira linha por ser o header

    while((fgets(line, sizeof(line), musics) != NULL)){
        strcpy(original_line, line); // assim temos uma copia da linha para depois escrever os erros no csv
        // outra ideia era nao ter outra variavel para a linha, mas enviar todos os argumentos para a funcao de escrita no ficheiro e delimitar com ";"
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
        // parsed++;
        // printf("ID: %li | Lyrics: %s \n",id,lyrics);
        
        if(isFormatValid(artist_id) && verify_year(year) && verify_duration(duration)){
            //verified++;
            artist_id_converted = convertID(artist_id, &num_artists); // daqui temos o array de ids de artistas + o num_artists calculado
            Music* m = createMusic(id, title, artist_id_converted, num_artists, duration, genre, year, lyrics);
            //addMusic(music_table, m);
            // chama func para escrever no csv a linha (quando esta correta)
            free(artist_id_converted);
        }
       
        else{
            //erros++;
            writeErrors(original_line, 2);
        }   

    }
    // printf("Foram lidos %d dados, foram validados %d dados e foram encontrados %d erros.\n", parsed, verified, erros);

    fclose(musics);
}

//Função responsável por ler e fazer parse de um arquivo CSV de users.
int parse_user_csv(const char *filename){
    
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
            
            char *username = NULL; //strcpy para NULL da seg error? 
            char *email = NULL;
            char *first_name = NULL;
            char *last_name = NULL;
            char *birth_date = NULL;
            char *country = NULL;
            char *subscription_type = NULL;
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
}
// Verificar/Corrigir os apontadores e os endereços nas chamadas de funções.
