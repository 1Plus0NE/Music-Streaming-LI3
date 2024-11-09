#include "../../include/parser/parser.h"
#define MAX_FILENAME 1024
#define MAX_LINE 2048
#define MAX_QUERYLINE 150

// Função principal de parse que chama os módulos de parse individualmente
void parse_all(char* path, GestorArtist* gestorArtist, GestorMusic* gestorMusic, GestorUser* gestorUser){
    //parse de artistas
    parse_artist(path, gestorArtist);

    //parse de músicas
    parse_music(path, gestorMusic, gestorArtist);

    //parse de usuários
    parse_user(path, gestorUser, gestorMusic);
}

void parse_queries(char* path, GestorUser* gestorUser, GestorMusic* gestorMusic, GestorArtist* gestorArtist){
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
    disco = fillWithArtists(gestorArtist, disco);
    printf("Preenchimento disco com artistas bem sucedido\n");

    disco = updateArtistsDurationFromMusic(gestorMusic, disco);
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
            query1(user, gestorUser, outputQ1);
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
       
         else if(line[0] == '3'){
            outputQ3 = fopen(outputPath, "w");
            if(!outputQ3){
                perror("Erro ao criar o ficheiro de output da query 3.\n");
                exit(EXIT_FAILURE);
            }

            strsep(&linePtr, " ");
            ageMin = atoi(strsep(&linePtr, " "));
            ageMax = atoi(strsep(&linePtr, "\n"));
            query3(ageMin, ageMax, gestorUser, gestorMusic, outputQ3);

            fclose(outputQ3);
        } 
        else continue;
     
    }
    freeDiscography(disco);
    fclose(queries);
}