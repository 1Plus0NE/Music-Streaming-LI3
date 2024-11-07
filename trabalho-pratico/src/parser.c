#include "../include/parser.h"
#define MAX_FILENAME 1024
#define MAX_LINE 2048
#define MAX_QUERYLINE 150

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
    int erros = 0;

    //argumentos para a struct de artistas
    char *id_str;
    long int id;
    char* name;
    char* description;
    char* rps_str;
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
        rps_str = (remove_aspas(strsep(&tmp_line,";")));
        recipe_per_stream = atof(rps_str);
        free(rps_str);
        id_constituent = remove_aspas(strsep(&tmp_line,";"));
        country = remove_aspas(strsep(&tmp_line,";"));
        type_str = remove_aspas(strsep(&tmp_line,"\n"));
        //type = stringToArtistType(type_str); -> quero verificar primeiro se o field é válido

        if(isFormatValid(id_constituent) && verifyConstituent(type_str,id_constituent)){
            type = stringToArtistType(type_str);
            id_constituent_converted = convertID(id_constituent, &num_constituent);
            Artist* a = createArtist(id, name, description, recipe_per_stream, id_constituent_converted, num_constituent, country, type);
            addArtist(artist_table,a);
            free(id_constituent_converted);
        }
       
        else{
            erros++;
            writeErrors(original_line, 1);
        }   
        free(id_str);
        free(name);
        free(description);
        free(id_constituent);
        free(country);
        free(type_str);
    }
    printf("Foram encontrados %d erros.\n", erros);
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
    char* year_str;
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
        year_str = (remove_aspas(strsep(&tmp_line,";")));
        year = atoi(year_str);
        free(year_str); // Fazemos free já que não vamos precisar mais 
        lyrics = remove_aspas(strsep(&tmp_line,"\n")); //as lyrics tem o \n lá porque é onde ha mudanca de linha

        if(isFormatValid(artist_id) && verify_year(year) && verify_duration(duration)){
            artist_id_converted = convertID(artist_id, &num_artists); // daqui temos o array de ids de artistas + o num_artists calculado
            if(validateArtistIDs(artist_table, artist_id_converted ,num_artists)){
                    Music* m = createMusic(id, title, artist_id_converted, num_artists, duration, genre, year, lyrics);
                    addMusic(music_table, m);
                    free(artist_id_converted);
            }
            else{
                free(artist_id_converted); // fazemos free se ele nao entra no if
                writeErrors(original_line, 2);
            }         
        }
       
        else{
            erros++;
            writeErrors(original_line, 2);
        }   

        free(id_str);
        free(title);
        free(artist_id);
        free(duration);
        free(genre);
        free(lyrics);

    }
    printf("Foram encontrados %d erros\n",erros);
    fclose(musics);
}

// função para ler e fazer parse de um ficheiro CSV de artistas.
void parse_user(char* path, GHashTable* userTable, GHashTable* musicTable){
    //variáveis para o parse
    FILE* users;
    char filename[MAX_FILENAME];
    char line[MAX_LINE];
    char original_line[MAX_LINE];
    char *tmp_oriLine=NULL;

    //argumentos para a struct de artistas
    char* username;
    char* email;
    char* first_name;
    char* last_name;
    char* birth_date;
    char* country;
    SubscriptionType subscription;
    char* liked_musics_id; // Para depois converter para long int
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
        if(userLineVerify(line, musicTable) == 0){
            // Trocar tmp_oriLine para original_line?
            username = remove_aspas(strsep(&tmp_oriLine, ";"));
            email = remove_aspas(strsep(&tmp_oriLine, ";"));
            first_name = remove_aspas(strsep(&tmp_oriLine,";"));
            last_name = remove_aspas(strsep(&tmp_oriLine,";"));
            birth_date = remove_aspas(strsep(&tmp_oriLine,";"));
            country = remove_aspas(strsep(&tmp_oriLine,";"));
            char* tmpSub = remove_aspas(strsep(&tmp_oriLine,";"));
            subscription = stringToSubscriptionType(tmpSub);
            //liked_musics_id_converted = convertID(remove_aspas(strsep(&tmp_oriLine,"\n")), &num_liked_musics);
            liked_musics_id = remove_aspas(strsep(&tmp_oriLine,"\n"));
            liked_musics_id_converted = convertID(liked_musics_id,&num_liked_musics);
            User* u = createUser(username, email, first_name, last_name, birth_date, country, subscription, liked_musics_id_converted, num_liked_musics);
            addUser(userTable, u);

            free(liked_musics_id_converted);
            free(liked_musics_id);
            free(username);
            free(email);
            free(first_name);
            free(last_name);
            free(birth_date);
            free(country);
            free(tmpSub);
            parsed++;
        }
        else{
            erros++;
            writeErrors(original_line, 3);
        } 

    }
    printf("Foram lidos %d dados e foram encontrados %d erros.\n", parsed, erros);

    fclose(users);
}

void parse_queries(char* path, GHashTable* userTable, GHashTable* musicTable, GHashTable* artistTable){
    
    char line[MAX_QUERYLINE];
    char* linePtr=NULL;
    FILE* queries;
    FILE* outputQ1;
    FILE* outputQ2;
    FILE* outputQ3;
    int command = 0; // Para escrita individual de ficheiros de output
    char outputPath[MAX_FILENAME]; // Caminho para ficheiros de output individuais

    
    char* user; // Utilizador para a query 1
    int nArtists = 0; // Nº de artistas para a query 2
    char* country; // País para a query 2
    Discography* disco = NULL; // Discografia para a query 2
    int ageMin = 0; // Idade mínima para a query 3
    int ageMax = 0; // Idade máxima para a query 3
    
    // Abertura ficheiro de input das queries
    queries = fopen(path, "r");
    if(!queries){
        perror("Erro ao abrir o ficheiro input das queries.\n");
        exit(EXIT_FAILURE);
    }


    // Discografia antes de resolver a Query2 
    disco = fillWithArtists(artistTable, disco);
    printf("Preenchimento disco com artistas bem sucedido\n");

    disco = updateArtistsDurationFromMusic(musicTable, disco);
    printf("Duração de cada discografia bem sucedida\n");

    sortByDuration(&disco);
    printf("Ordenação disco bem sucedida\n");
    printf("Inicio Queries\n");
    // discografia pronta para a 2ª query


    // Leitura query a query
    while(fgets(line, sizeof(line), queries) != NULL){ 

        linePtr = line;  
        // Atualização do path para o ficheiro de output da query 
        command++;
        snprintf(outputPath, MAX_FILENAME, "resultados/command%d_output.txt", command);
        
        // Identificação da Query
        if(line[0] == '1'){
            // Criação do ficheiro de output da query para argumento do função query1
            outputQ1 = fopen(outputPath, "w");
            if(!outputQ1){
                perror("Erro ao criar o ficheiro de output da query 1.\n");
                exit(EXIT_FAILURE);
            }
            // Tratamento da linha para a 1ª Query
            strsep(&linePtr, " "); // Ignora o id da Query e o espaço 
            user = strsep(&linePtr, "\n");
            query1(user, userTable, outputQ1);
            // Processo completo, fechar ficheiro
            fclose(outputQ1);
        }
        else if(line[0] == '2'){
            outputQ2 = fopen(outputPath, "w");
            if(!outputQ2){
                perror("Erro ao criar o ficheiro de output da query 2.\n");
                exit(EXIT_FAILURE);
            }

            strsep(&linePtr, " ");
            nArtists = atoi(strsep(&linePtr, " ")); // Numero de artistas
            country = remove_aspas(strsep(&linePtr, "\n")); // País sem aspas
            // Substiruir os NULLs
            if(country==NULL) query2(nArtists, disco, outputQ2); // query 2 sem especificação de país
            else query2b(nArtists, country, disco, outputQ2); // query 2 com país especificado
            
            if(country != NULL){
                free(country);
            }
            
            fclose(outputQ2);
        }
       
        /* else if(line[0] == '3'){
            outputQ3 = fopen(outputPath, "w");
            if(!outputQ3){
                perror("Erro ao criar o ficheiro de output da query 3.\n");
                exit(EXIT_FAILURE);
            }

            strsep(&linePtr, " ");
            ageMin = atoi(strsep(&linePtr, " "));
            ageMax = atoi(strsep(&linePtr, "\n"));
            query3(ageMin, ageMax, userTable, musicTable, outputQ3);

            fclose(outputQ3);
        } */
        // Ignora Query inválida
        // Criar um ficheiro vazio?
        else continue;
     
    }
    freeDiscography(disco);
    fclose(queries);
}