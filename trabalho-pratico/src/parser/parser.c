#include "parser.h"

// Função que cria a diretoria "dataset-errors" e respetivos ficheiros com cabeçalhos
    // Possivelmente inutil, mudar módulo posteriormente
void errorsDir(){
    // Criação da diretoria
    if (mkdir("../dataset-errors", 0777) == -1) {
        if (errno == EEXIST) printf("Diretoria já existente.\n");
        else {
            perror("Erro ao criar a diretoria.\n");
            exit(EXIT_FAILURE);
        }
    }
    else printf("dataset-errors criado com sucesso.\n");

    // Ficheiros de erros com respetivos cabeçalhos
    FILE *errors = fopen("../dataset-errors/users.csv", "w");
    if(!errors){
        perror("Erro ao criar o ficheiro de erros de users.\n");
        exit(EXIT_FAILURE);
    }
    fprintf(errors, "\"username\";\"email\";\"first_name\";\"last_name\";\"birth_date\";\"country\";\"subscription_type\";\"liked_songs_id\"\n");
    fclose(errors);

    fopen("../dataset-errors/artists.csv", "w");
    if(!errors){
        perror("Erro ao criar o ficheiro de erros de artists.\n");
        exit(EXIT_FAILURE);
    }
    fprintf(errors, "\"id\";\"name\";\"description\";\"recipe_per_stream\";\"id_constituent\";\"country\";\"type\"\n");
    fclose(errors);

    fopen("../dataset-errors/musics.csv", "w");
    if(!errors){
        perror("Erro ao criar o ficheiro de erros de musics.\n");
        exit(EXIT_FAILURE);
    }
    fprintf(errors, "\"id\";\"title\";\"artist_id\";\"duration\";\"genre\";\"year\";\"lyrics\"\n");
    fclose(errors);
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

void parse_musics(char* path){
    // Variaveis para o parse
    FILE* musics;
    char filename[1024];
    char line[2048];
    char *tmp_line=NULL;

    // Argumentos para a struct de musicas
    long int id;
    char* title;
    char* artist_id;
    long int* artist_id_converted;
    int num_artists;
    char* duration;
    char* genre;
    int year;
    char* lyrics;
    
    int erros=1; // a primeira linha n conta

    // music_table = createMusicTable();
    snprintf(filename,1024,"%s/musics.csv",path); //abrir ficheiro de musicas

    musics = fopen(filename, "r");
    if(!file){
        perror("Erro ao abrir o ficheiro csv das musicas.\n");
        exit(EXIT_FAILURE);
    }

    fgets(line, sizeof(line), musics); //skip da primeira linha por ser o header

    while((fgets(line, sizeof(line), musics) != NULL)){
        tmp_line= line;
        id = atoi(strsep(&tmp_line,";"));
        title  = strsep(&tmp_line,";");
        artist_id  = strsep(&tmp_line,";");
        duration  = strsep(&tmp_line,";");
        genre  = strsep(&tmp_line,";");
        year = atoi(strsep(&tmp_line,";"));
        lyrics = stsep(&tmp_line,";") //as lyrics tem o \n lá porque é onde ha mudanca de linha
        removeEnters(lyrics);
        /*
        if(isFormatValid(artist_id) && verify_year(year) && verify_music(duration)){
            
            artist_id_converted = convertID(artist_id, &num_artists);
            Music* m = createMusic(id, title, artist_id_converted, num_artists, duration, genre, year, lyrics);
            addMusic(music_table, m);
            // chama func para escrever no csv a linha (quando esta correta)
        }*/
       /*
        else{
            erros++;
            chama func para escrever no csv das musicas erradas a linha (tmp_line)
        }
       
       */

    }
    fclose(musics);
}


// Função para ler e fazer parse de um CSV file de musicas.
int parse_musics_csv(const char* filename) {
    FILE* file = fopen(filename, "r");

    if(!file){
        perror("Erro ao abrir o ficheiro csv das musicas.\n");
        exit(EXIT_FAILURE);
    }

    char line[512];

    fgets(line, sizeof(line), file); //skip da primeira linha por ser o header

    // Path para o ficheiro de erros dos users 
        //Supõe-se que o ficheiro e diretoria ja estejam criados pela função errorsDir
    char *errorsMusics = "../dataset-errors/musics.csv";

    while(fgets(line, sizeof(line), file)){
        if(musicLineVerify(line) == 0){
            int id;
            char* title = NULL;
            int* artist_id = NULL;
            int num_artists = 0;
            char* duration = NULL;
            char* genre = NULL;
            int year;
            char* lyrics = NULL;
            
            // copia da linha para usarmos o strsep
            char* line_copy = strdup(line);
            char* token = line_copy; 
            char* campo;

            for(int i = 0; i <= 6; i++){
                campo = strsep(&token, ";");

                if(campo){
                    switch(i){
                        case 0:
                            id = atoi(remove_aspas(campo));
                            break;
                        case 1:
                            title = strdup(remove_aspas(campo));
                            break;
                        case 2:
                            char* artist_list = remove_aspas(campo);

                            // quantos artistas existem
                            char* tmp = artist_list;
                            num_artists = 1;  // vamos assumir que existe pelo menos 1 
                            while (*tmp) {
                                if (*tmp == ',') {
                                    num_artists++;
                                }
                                tmp++;
                            }

                            artist_id = malloc(num_artists * sizeof(int));

                            char* artist_token;
                            int artist_index = 0;
                            while ((artist_token = strsep(&artist_list, ",")) != NULL && artist_index < num_artists) {
                                artist_id[artist_index++] = atoi(artist_token);
                            }
                            break;                       
                        case 3:
                            duration = strdup(remove_aspas(campo));
                            break;
                        case 4:
                            genre = strdup(remove_aspas(campo));
                            break;
                        case 5:
                            year = atoi(remove_aspas(campo));
                            break;
                        case 6:
                            lyrics = strdup(remove_aspas(campo));
                            break;
                        default:
                            break;
                    }
                }
            }
            
            //Music* m = createMusic(id, title, artist_id, num_artists, duration, genre, year, lyrics);
            printf("Criada a musica: %s no de artistas: %d, duracao: %s\n", title, num_artists, duration); // print de teste
            //local onde depois será feita o armazenamento na hashtable(estrutura de dados)

            free(line_copy); 
            free(title);
            free(artist_id);
            free(duration);
            free(genre);
            free(lyrics);
        }      
        else{

            FILE *musicErrors = fopen(errorsMusics, "a");
            fputs(line, musicErrors);
            fclose(musicErrors);
        }  
    }
    fclose(file);
    return 0;
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