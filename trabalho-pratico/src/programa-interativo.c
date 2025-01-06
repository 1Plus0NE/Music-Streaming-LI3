#include "../include/programa-interativo.h"

void printMenu(){
    printf(COLOR_BLUE"\n=== Menu de Queries ===\n" COLOR_RESET);
    printf(COLOR_CYAN"1 - Query 1: Listar o resumo de um utilizador ou artista, consoante o identificador recebido por argumento.\n");
    printf("2 - Query 2: Quais são os top N artistas com maior discografia?\n");
    printf("3 - Query 3: Quais são os géneros de música mais populares numa determinada faixa etária?\n");
    printf("4 - Query 4: Qual é o artista que esteve no top 10 mais vezes?\n");
    printf("5 - Query 5: Recomendação de utilizadores com gostos parecidos\n");
    printf("6 - Query 6: Resumo anual para um utilizador\n");
    printf("0 - Sair\n"COLOR_RESET);
    printf(COLOR_BLUE"=======================\n"COLOR_RESET);
    printf(COLOR_CYAN"Escolha uma opção: "COLOR_RESET);
}

int main(){
    char dataSetPath[256];
    int option = -1;

    printf(COLOR_CYAN"Introduza o caminho dos ficheiros de dados: " COLOR_RESET);
    if(fgets(dataSetPath, sizeof(dataSetPath), stdin) == NULL){
        printf("Erro ao ler o caminho dos ficheiros de dados.\n");
        return 1;
    }
    dataSetPath[strcspn(dataSetPath, "\n")] = '\0';

    printf(COLOR_CYAN"Dataset carregado...\n"COLOR_RESET);

    GestorArtist* gestorArtist = createGestorArtist();
    GestorMusic* gestorMusic = createGestorMusic();
    GestorUser* gestorUser = createGestorUser();
    GestorAlbum* gestorAlbum = createGestorAlbum();
    GestorHistory* gestorHistory = createGestorHistory();

    errosDir();
    parse_all(dataSetPath, gestorArtist, gestorMusic, gestorUser, gestorAlbum, gestorHistory);

    if(!gestorArtist || !gestorMusic || !gestorUser || !gestorAlbum || !gestorHistory){
        printf(COLOR_RED"Erro ao carregar o dataset. Verifique o caminho fornecido.\n" COLOR_RESET);
        return 1;
    }

    printf(COLOR_CYAN"Selecione o delimitador a utilizar: " COLOR_RESET);
    char delimiter;
    if(scanf(" %c", &delimiter) != 1){
        printf(COLOR_RED"Erro ao ler o delimitador. Tente novamente.\n" COLOR_RESET);
        while (getchar() != '\n');
    }

    while(option != 0){
        printMenu();
        if(scanf("%d", &option) != 1){
            printf(COLOR_RED"Opção inválida. Tente novamente.\n" COLOR_RESET);
            while (getchar() != '\n');
            continue;
        }

        switch(option){
            case 1:
                char id[50];
                printf(COLOR_CYAN"Introduza o id (utilizador ou artista): " COLOR_RESET);
                scanf("%s", id);
                query1(id, gestorUser, gestorArtist, delimiter, stdout);
                break;
            case 2:
                int N;
                char country[50];
                Discography* disco = NULL;
                disco = fillWithArtists(gestorArtist, disco);
                disco = updateArtistsDurationFromMusic(gestorMusic, disco);
                sortByDuration(&disco);
                printf(COLOR_CYAN"Introduza o número de artistas (N): " COLOR_RESET);
                scanf("%d", &N);
                getchar();
                printf(COLOR_CYAN"Introduza o país (opcional, pressione Enter para ignorar): " COLOR_RESET);
                country[strcspn(country, "\n")] = '\0';
                if(strlen(country) == 0){
                    query2(N, NULL, disco, delimiter, stdout);
                }else{
                    query2(N, country, disco, delimiter, stdout);
                }
                freeDiscography(disco);
                break;
            case 3:
                int ageMin, ageMax;
                printf(COLOR_CYAN"Introduza a idade mínima: " COLOR_RESET);
                scanf("%d", &ageMin);
                printf(COLOR_CYAN"Introduza a idade máxima: " COLOR_RESET);
                scanf("%d", &ageMax);
                query3(ageMin, ageMax, gestorUser, delimiter, stdout);
                break;
            case 4:
                char beginDate[20], endDate[20];
                printf(COLOR_CYAN"Introduza a data inicial (YYYY/MM/DD) (opcional, pressione Enter para ignorar): " COLOR_RESET);
                fgets(beginDate, sizeof(beginDate), stdin);
                beginDate[strcspn(beginDate, "\n")] = '\0';
                printf(COLOR_CYAN"Introduza a data final (YYYY/MM/DD) (opcional, pressione Enter para ignorar): " COLOR_RESET);
                fgets(endDate, sizeof(endDate), stdin);
                endDate[strcspn(endDate, "\n")] = '\0';

                if(strlen(beginDate) == 0 || strlen(endDate) == 0){
                    //query4(); // caso sem datas
                }else{
                    //query4(e);
                }
                break;
            case 5:
                char username[50];
                int numUsers;
                printf(COLOR_CYAN"Introduza o nome de utilizador: " COLOR_RESET);
                scanf("%49s", username);
                printf(COLOR_CYAN"Introduza o número de utilizadores a recomendar: " COLOR_RESET);
                scanf("%d", &numUsers);
                query5(gestorHistory, username, numUsers, stdout);
                break;
            case 6:
                char userId[50];
                char year[5];
                char n_str[10];
                printf(COLOR_CYAN"Introduza o ID do utilizador: " COLOR_RESET);
                scanf("%49s", userId);
                printf(COLOR_CYAN"Introduza o ano (YYYY): " COLOR_RESET);
                scanf("%4s", year);
                printf(COLOR_CYAN"Introduza o número de artistas preferidos (opcional, pressione Enter para ignorar): " COLOR_RESET);
                char n[10];
                if(fgets(n, sizeof(n), stdin) && n[0] != '\n'){
                    sscanf(n, "%9s", n_str);
                }else{
                    n_str[0] = '\0';
                }
                query6(userId, year, n_str, gestorHistory, gestorMusic, delimiter, stdout);
                break;
            case 0:
                printf(COLOR_CYAN"A terminar o programa...\n" COLOR_RESET);
                return 0;
            default:
                printf(COLOR_RED"Opção inválida. Tente novamente.\n" COLOR_RESET);
        }
    }
    freeGestorArtist(gestorArtist);
    freeGestorMusic(gestorMusic);
    freeGestorUser(gestorUser);
    freeGestorAlbum(gestorAlbum);
    freeGestorHistory(gestorHistory);
    return 0;
}