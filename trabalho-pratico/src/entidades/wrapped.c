#include "../../include/entidades/wrapped.h"


// Lista ligada com dados de cada artista ouvido no wrapped
struct artistsTimes{
    long int* artistId;
    int listTime;
    long int* listMus;
    struct artistsTimes* next;    
};

// Estrutura com o wrapped
struct wrapped{
    char* ano; 
    long int userId; // Formato sem 0s
    int** albuns;
    int* horas; //horas[24]
    int* generos; // generos[10]
    int** dias;
    ArtistsTimes* artistsTimes;
};

// Estrutura com os dados para resolver a Query 6
// Possui a estrutura com a resposta da Query 6 (wrap)
// Possui a Hash de musicas necessária para passar como argumento para o foreachHistory
/*struct query6Data{
    Wrapped* wrap;
    GestorMusic* gestorMusic;
};*/

// ----------------------------------------------------------------INITS E FREES----------------------------------------------------------------
// Inicialização da estrutura para a Query 6
/*Query6Data* query6DataInit(){
    Query6Data* query6Data = (Query6Data*)malloc(sizeof(Query6Data));
    if(!query6Data){
        perror("Erro ao alocar memória na Query 6\n");
        exit(EXIT_FAILURE);
    }
    query6Data->wrap = wrappedInit();
    //query6Data->gestorMusic = NULL;
    query6Data->gestorMusic = createGestorMusic(); //NUU»LL?
    return query6Data;
}*/

// Inicializa a subestructura Wrapped
Wrapped* wrappedInit(){
    Wrapped* newWrapped = (Wrapped*)malloc(sizeof(Wrapped));
    if (newWrapped == NULL) {
        perror("Falha ao alocar memória para a estrutura 'Wrapped'");
        exit(EXIT_FAILURE);
    }

    newWrapped->ano = (char*)malloc(5*sizeof(char)); // Possivel causa de erro 5 para 2025+'\0'
    newWrapped->userId = 0;
    if(newWrapped->ano == NULL) {
        free(newWrapped->ano);
        free(newWrapped);
        perror("Falha ao alocar memória para o ano na estrutura 'Wrapped'");
        exit(EXIT_FAILURE);
    }

    // Alocação do array horas e inicialização com 0s
    newWrapped->horas = (int*)malloc(24*sizeof(int));
    if(!newWrapped->horas){
        free(newWrapped->ano);
        free(newWrapped->horas);
        free(newWrapped);
        perror("Erro ao alocar memória para o array de horas, função 'wrappedInit'\n");
        exit(EXIT_FAILURE);
    }
    // Inicialização com 0s
    for (int i = 0; i < 24; i++) {
        newWrapped->horas[i] = 0;
    }

    // Alocação do array generos e inicialização com 0s
    newWrapped->generos = (int*)malloc(10*sizeof(int));
    if(!newWrapped->generos){
        free(newWrapped->ano);
        free(newWrapped->horas);
        free(newWrapped->generos);
        free(newWrapped);
        perror("Erro ao alocar memória para o array de generos, função 'wrappedInit'\n");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < 10; i++){
        newWrapped->generos[i] = 0;
    }

    // Inicialização de 'dias' ou calendario
    // Alocar memória para o array de ponteiros para as linhas a '0'
    newWrapped->dias = (int**)malloc(12 * sizeof(int*));
    if (!newWrapped->dias) {
        free(newWrapped->ano);
        free(newWrapped->horas);
        free(newWrapped->generos);
        free(newWrapped->dias);
        free(newWrapped);
        perror("Erro ao alocar memória para as linhas da matriz, função 'wrappedInit'\n");
        exit(EXIT_FAILURE);
    }

    // Alocar memória para 31 colunas para cada mês e inicializar com 0
    for (int i = 0; i < 12; i++) {
        newWrapped->dias[i] = (int*)malloc(31 * sizeof(int));
        if(!newWrapped->dias[i]){
            free(newWrapped->ano);
            free(newWrapped->horas);
            free(newWrapped->generos);
            for (int j = 0; j < i; j++) {
                free(newWrapped->dias[j]);  // Libera a memória já alocada 
            }
            free(newWrapped->dias);
            free(newWrapped);    
            perror("Erro ao alocar memória para as colunas da matriz, função 'wrappedInit'\n");
            exit(EXIT_FAILURE);
        }
    
        // Inicializa a memória com 0 (mes individual)
        for (int j = 0; j < 31; j++) {
            newWrapped->dias[i][j] = 0;
        }
    }

    // Alocação e inicialização do array de albuns e do array com os seus tempos
    newWrapped->albuns = (int**)malloc(2 * sizeof(int*));
    if (!newWrapped->albuns){
        free(newWrapped->ano);
        free(newWrapped->horas);
        free(newWrapped->generos);
        for (int i = 0; i < 12; i++){
            for(int j = 0; j < i; j++){
                free(newWrapped->dias[j]);
            } 
        }
        free(newWrapped->dias);
        free(newWrapped->albuns);
        free(newWrapped);
        perror("Falha ao alocar memória para albuns");
        exit(EXIT_FAILURE);
    }

    newWrapped->albuns[0] = (int*)malloc(1*sizeof(int)); // 1ª linha: códigos dos álbuns, inicializada com 0
    newWrapped->albuns[1] = (int*)malloc(1*sizeof(int)); // 2ª linha: segundos, inicializada com 0

    if (!newWrapped->albuns[0] || !newWrapped->albuns[1]) {
        free(newWrapped->ano);
        free(newWrapped->horas);
        free(newWrapped->generos);
        for (int i = 0; i < 12; i++){
            for(int j = 0; j < i; j++){
                free(newWrapped->dias[j]);
            } 
        }
        free(newWrapped->dias);
        free(newWrapped->albuns);
        free(newWrapped);
        perror("Falha ao alocar memória para álbuns individuais");
        exit(EXIT_FAILURE);
    }
    // Inicialização com 0s
    newWrapped->albuns[0][0] = 0;
    newWrapped->albuns[1][0] = 0;

    // Inicialização da Lista Ligada da estrutura
    newWrapped->artistsTimes = NULL;

    return newWrapped;
}

// Libertação de memória da subestrutura Wrapped
/*void freeWrapped(Wrapped* wrap) {
    if(!wrap) return;

    free(wrap->ano);

    // Liberta memória alocada para os álbuns
    free(wrap->albuns[0]); // Liberta os códigos dos álbuns
    free(wrap->albuns[1]); // Liberta o tempo dos álbuns
    free(wrap->albuns);    // Liberta o array principal


    free(wrap->horas);
    free(wrap->generos);

    // Liberta a memoria alocada para dias
    for(int i = 0; i < 12; i++){    // Liberta Mes a mes
        free(wrap->dias[i]);
    }
    free(wrap->dias);

    // Liberta memória alocada para a lista de ArtistsTimes
    while (wrap->artistsTimes != NULL){
        ArtistsTimes* aux = wrap->artistsTimes;
        wrap->artistsTimes = wrap->artistsTimes->next;
        // Liberta memória alocada para artistId
        free(aux->artistId);
        free(aux->listMus);
        free(aux);
    }
    // liberta o ponteiro para a estrutura principal ?
    free(wrap);
}*/
void freeWrapped(Wrapped* wrapped) {
    if (wrapped == NULL) {
        return; // Se o ponteiro for NULL, não faz nada.
    }

    // Liberação da memória para 'ano'
    if (wrapped->ano != NULL) {
        free(wrapped->ano);
    }

    // Liberação do array de 'horas'
    if (wrapped->horas != NULL) {
        free(wrapped->horas);
    }

    // Liberação do array 'generos'
    if (wrapped->generos != NULL) {
        free(wrapped->generos);
    }

    // Liberação da matriz 'dias' (12 meses e 31 dias por mês)
    if (wrapped->dias != NULL) {
        for (int i = 0; i < 12; i++) {
            if (wrapped->dias[i] != NULL) {
                free(wrapped->dias[i]); // Libera as colunas de cada mês
            }
        }
        free(wrapped->dias); // Libera o array de ponteiros para os meses
    }

    // Liberação da matriz 'albuns' (2 linhas: códigos e tempos)
    if (wrapped->albuns != NULL) {
        if (wrapped->albuns[0] != NULL) {
            free(wrapped->albuns[0]); // Libera a 1ª linha (códigos dos álbuns)
        }
        if (wrapped->albuns[1] != NULL) {
            free(wrapped->albuns[1]); // Libera a 2ª linha (tempos dos álbuns)
        }
        free(wrapped->albuns); // Libera o array de ponteiros
    }

    // Liberação da lista ligada 'artistsTimes'
    while (wrapped->artistsTimes != NULL) {
        ArtistsTimes* next = wrapped->artistsTimes->next;
        
        // Libera os arrays na estrutura 'ArtistsTimes'
        if (wrapped->artistsTimes->listMus != NULL) {
            free(wrapped->artistsTimes->listMus);
        }
        if (wrapped->artistsTimes->artistId != NULL) {
            free(wrapped->artistsTimes->artistId);
        }
        
        free(wrapped->artistsTimes); // Libera a própria estrutura 'ArtistsTimes'
        wrapped->artistsTimes = next; // Avança para o próximo nó
    }

    // Libera o ponteiro principal 'Wrapped'
    free(wrapped);
}


// ----------------------------------------------------------------FUNÇÕES----------------------------------------------------------------
// Função que cria uma lista com respetivos valores para adicionar ao fim da lista existente
ArtistsTimes* newArtistTime(long int* idArtist, int numArtists, long int idMusic, int segundos){
    ArtistsTimes* newAT = (ArtistsTimes*)malloc(sizeof(ArtistsTimes));
    if(!newAT){
        free(newAT);
        perror("Erro ao alocar memória na função 'setArtistTime'.\n");
        exit(EXIT_FAILURE);
    }
    
    newAT->listMus = (long int*)malloc(2*sizeof(long int));
    if(!newAT->listMus){
        free(newAT);
        perror("Erro ao alocar memória para a lista de musicas na função 'newArtistTime'.\n");
        exit(EXIT_FAILURE);
    }
    newAT->artistId = (long int*)malloc((numArtists+1)*sizeof(long int));
    if(!newAT->artistId){
        free(newAT->listMus);
        free(newAT);
        perror("Erro ao alocar memória para a lista de artistas na função 'newArtistTime'.\n");
        exit(EXIT_FAILURE);
    }
    // Fazer completar array de artistas acabar com 0
    for(int i=0;i<numArtists;i++){
       newAT->artistId[i] = idArtist[i];
    }
    newAT->artistId[numArtists] = 0;
    newAT->listTime = segundos;
    newAT->listMus[0] = idMusic;
    newAT->listMus[1] = 0;
    newAT->next = NULL;

    return newAT;
}
// Função que procura uma musica por id na lista de um artista no Wrapped
void procuraMusica(long int* listMus, long int idMusic){
    
    int i=0;
    while(listMus[i]!=0){
        if(listMus[i] == idMusic) return;
        i++;
    }
    listMus=(long int*)realloc(listMus, (i+2)*sizeof(long int));
    listMus[i] = idMusic;
    listMus[i+1] = 0; // Novo fim da lista
}
// Função que verifica se os artistas recebidos de um histórico, são os mesmos numa lista da lista ligada ArtistsTimes
int listaArtistasIguais(long int* artistaHist, int numArtistsHist, long int* artistaWrap){
    int i=0;
    for(;i<numArtistsHist;i++){
        if(artistaHist[i] != artistaWrap[i]) return 1;
    }
    // Caso em que o artista no wrap tem mais elementos
    if(artistaWrap[i]!=0) return 1;
    // Caso em que sao iguais
    return 0;
}

// ----------------------------------------------------------------GETS E SETS----------------------------------------------------------------

char* getWrapAno(Wrapped* wrap){
    return wrap->ano ? strdup(wrap->ano) : NULL;
}

long int getWrapUserId(Wrapped* wrap){
    return wrap ? wrap->userId : 0;
}

// Como evitar enviar diretamente apontadores para arrays de inteiros
int** getWrapAlbuns(Wrapped* wrap){
    return wrap->albuns ? wrap->albuns : NULL;
}

int* getWrapHoras(Wrapped* wrap){
    return wrap->horas ? wrap->horas : NULL;
}

int* getWrapGeneros(Wrapped* wrap){
    return wrap->generos ? wrap->generos : NULL;
}

int** getWrapDias(Wrapped* wrap){
    return wrap->dias ? wrap->dias : NULL;
}

ArtistsTimes* getWrapArtistsTimes(Wrapped* wrap){
    return wrap->artistsTimes ? wrap->artistsTimes : NULL;
}

long int* getArtistTimesArtistId(ArtistsTimes* at){
    return at->artistId ? at->artistId : NULL;
}

int getArtistTimesListTime(ArtistsTimes* at){
    return at ? at->listTime : 0;
}

long int* getArtistTimesListMus(ArtistsTimes* at){
    return at->listMus ? at->listMus : NULL;
}

ArtistsTimes* getArtistTimesNext(ArtistsTimes* at){
    return at->next ? at->next : NULL;
}

void setWrapAno(Wrapped* wrap, char* ano){
    if(wrap){
        if(wrap->ano){
            free(wrap->ano);
        }
        wrap->ano = strdup(ano);
    }
}

void setWrapUserId(Wrapped* wrap, long int userId){
    if(wrap){
        wrap->userId = userId;
    }
}

void setWrapAlbum(Wrapped* wrap, long int albumId, int segundos){
    int albumCount = 0;
    
    if(!wrap->albuns){
        perror("Array albuns null, (setWrapAlbum)");
        return;
    }

    // Verificar se o álbum já existe
    while (wrap->albuns[0][albumCount] != 0) { // Assume que 0 significa que não há álbum nesse índice
        if (wrap->albuns[0][albumCount] == albumId) {
            // Se o álbum já existe, incrementa os segundos
            wrap->albuns[1][albumCount] += segundos;
            return;
        }
        albumCount++;
    }

    // Se não encontrou o álbum, adiciona um novo
    // Redimensiona a matriz para adicionar um novo álbum 
    wrap->albuns[0] = (int*)realloc(wrap->albuns[0], (albumCount + 2) * sizeof(int));
    wrap->albuns[1] = (int*)realloc(wrap->albuns[1], (albumCount + 2) * sizeof(int));

    if (!wrap->albuns[0] || !wrap->albuns[1]) {
        free(wrap->albuns);
        perror("Falha ao redimensionar memória para albuns");
        exit(EXIT_FAILURE);
    }

    // Inicializa o novo espaço com zero
    wrap->albuns[0][albumCount+1] = 0;
    wrap->albuns[1][albumCount+1] = 0;

    // Adiciona o novo álbum (espaço anterior)
    wrap->albuns[0][albumCount] = albumId;
    wrap->albuns[1][albumCount] = segundos;
}
void setWrapHoras(Wrapped* wrap, char* hora, int segundos){
        // Processo para retirar apenas a hora em formato int do timeStamp
        char* horaCopia = (char*)malloc(20*sizeof(char));
        strcpy(horaCopia, hora);
        char* horaCopiaAux = horaCopia;
        //char* horaCopiaAux = horaCopia;
        
        strsep(&horaCopia, " ");
        char* horaStr;
        horaStr = strsep(&horaCopia, ":");
        int horaInt = atoi(horaStr);
        if(horaInt < 0 || horaInt > 23){
            free(horaCopiaAux);
            //free(horaStr);
            perror("Hora invalida apos conversão, função 'setWrapHoras'\n");
            exit(EXIT_FAILURE);
        }

        wrap->horas[horaInt] += segundos;
        free(horaCopiaAux);
        //free(horaStr);
}

void setWrapGeneros(Wrapped* wrap, char* genero, int segundos){
    /* Vamos considerar para cada índice do array:
    1 - Blues || 2 - Classical || 3 - Country || 4 - Electronic || 5 - HipHop
    6 - Jazz || 7 - Metal || 8 - Pop || 9 - Reggae || 10 - Rock */
    if(wrap){
        if(strcmp(genero, "Blues") == 0)  wrap->generos[0] += segundos;
        else if(strcmp(genero, "Classical") == 0) wrap->generos[1] += segundos;
        else if(strcmp(genero, "Country") == 0) wrap->generos[2] += segundos;
        else if(strcmp(genero, "Electronic") == 0) wrap->generos[3] += segundos;
        else if(strcmp(genero, "Hip Hop") == 0) wrap->generos[4] += segundos;
        else if(strcmp(genero, "Jazz") == 0) wrap->generos[5] += segundos;
        else if(strcmp(genero, "Metal") == 0) wrap->generos[6] += segundos;
        else if(strcmp(genero, "Pop") == 0) wrap->generos[7] += segundos;
        else if(strcmp(genero, "Reggae") == 0) wrap->generos[8] += segundos;
        else if(strcmp(genero, "Rock") == 0) wrap->generos[9] += segundos;
        else printf("Genero desconhecido, função 'setWrapGeneros'\n");
    }
}

void setWrapDias(Wrapped* wrap, char* data, int segundos){
        // Processo para retirar apenas o mes e o dia em formato int do timeStamp
        char* dataCopia = (char*)malloc(20*sizeof(char)); 
        strcpy(dataCopia, data);
        char* dataCopiaAux = dataCopia;
        //char* mes = (char*)malloc(3*sizeof(char));
        //char* dia = (char*)malloc(3*sizeof(char));
        
        strsep(&dataCopia, "/");
        char* mes = strsep(&dataCopia, "/");
        char* dia = strsep(&dataCopia, " ");
        int mesInt = atoi(mes);
        int diaInt = atoi(dia);
        if(mesInt < 1 || mesInt > 12 || diaInt < 1 || diaInt > 31){
            //free(mes);
            //free(dia);
            free(dataCopiaAux);
            perror("Data invalida apos conversão, função 'setWrapDias'\n");
            exit(EXIT_FAILURE);
            //return;
        }
        wrap->dias[mesInt-1][diaInt-1] = segundos;
        //free(mes);
        //free(dia);
        free(dataCopiaAux);
}

void setWrapArtistTime(Wrapped* wrap, long int* idArtist, int numArtists, long int idMusic, int segundos){

    // Caso a lista esteja vazia, inicialize-a
    if (wrap->artistsTimes == NULL) {
        wrap->artistsTimes = newArtistTime(idArtist, numArtists, idMusic, segundos);
        return;
    }

    // Use um ponteiro auxiliar para percorrer a lista
    ArtistsTimes* current = wrap->artistsTimes;

    while (current != NULL) {
        // Verifica se o artista já existe na lista
        if (listaArtistasIguais(current->artistId, numArtists, idArtist) == 0) {
            current->listTime += segundos;
            procuraMusica(current->listMus, idMusic);
            return;
        }
        // Se for o último nó, adiciona um novo nó ao final
        else if (current->next == NULL) {
            current->next = newArtistTime(idArtist, numArtists, idMusic, segundos);
            return;
        }
        // Avança para o próximo nó
        current = current->next;
    }
}
// Função que calcula o total tempo de musica ouvido e altera a variavel totalGenre para ficar já definido o genero mais ouvido
char* getWrapTotalListTime(Wrapped* wrap, char** totalGenre){
    int max=0;
    int indice=10;
    int total=0; 
    for(int i = 0; i < 10; i++){
        if(wrap->generos[i]>max){
            max = wrap->generos[i];
            indice = i;
        }
        total += wrap->generos[i];
    }

    // Alterar o totalGenre (genero mais ouvido)
    if(indice == 0){ strcpy(*totalGenre, "Blues"); (*totalGenre)[5] = '\0'; }
    else if(indice == 1){ strcpy(*totalGenre, "Classical"); (*totalGenre)[9] = '\0'; }
    else if(indice == 2){ strcpy(*totalGenre, "Country"); (*totalGenre)[7] = '\0'; }
    else if(indice == 3){ strcpy(*totalGenre, "Electronic"); (*totalGenre)[10] = '\0'; }
    else if(indice == 4){ strcpy(*totalGenre, "Hip Hop"); (*totalGenre)[7] = '\0'; }
    else if(indice == 5){ strcpy(*totalGenre, "Jazz"); (*totalGenre)[4] = '\0'; }
    else if(indice == 6){ strcpy(*totalGenre, "Metal"); (*totalGenre)[5] = '\0'; }
    else if(indice == 7){ strcpy(*totalGenre, "Pop"); (*totalGenre)[3] = '\0'; }
    else if(indice == 8){ strcpy(*totalGenre, "Reggae"); (*totalGenre)[6] = '\0'; }
    else if(indice == 9){ strcpy(*totalGenre, "Rock"); (*totalGenre)[4] = '\0'; }
    else{ strcpy(*totalGenre, "Genero Desconhecido"); (*totalGenre)[19] = '\0'; }
    
    // Cenário em que não foram adicionados históricos, (para outpu \n)
    if(total==0){
        char* strTotal = NULL;
        return strTotal;

    }
    // Transformar total no formato hh:mm:ss
    char* strTotal = secondsToString(total);
    return strTotal;
}

// Funciona que percorre a lista de artistas, ignorando o/s artista/s e os listening Times, contando apenas os ids de musicas em toda a lista
char* getWrapTotalMusics(Wrapped* wrap){
    int contador = 0;
    ArtistsTimes* current = wrap->artistsTimes;
    while (current != NULL) {
        for (int i = 0; current->listMus[i] != 0; i++) {
            contador++;
        }
        current = current->next;
    }
    // Converter em String
    char* strContador = (char*)malloc(4*sizeof(char)); // Suporta ate 999 nMusicas
    sprintf(strContador, "%d", contador);
    return strContador;
}

// Função para devolver o artista mais ouvido em formado do seu id
char* getWrapTotalArtist(Wrapped* wrap){
    
    long int* totalArtist = getArtistTimesArtistId(wrap->artistsTimes);
    char* strTotalArtist = (char*)malloc(9*sizeof(char));
    sprintf(strTotalArtist, "A%07ld", totalArtist[0]); // So nos interessa o 1º elemento, o numero ja sai formatado para output

    return strTotalArtist;
}

// Função que devolve o dia mais ouvido em formato char* (hh:mm:ss)
char* getWrapTotalDay(Wrapped* wrap){

    int mes = 0, dia = 0, max = 0, i, j;
    char* strTotalDay = (char*)malloc(11*sizeof(char));

    for(i=0; i<12; i++){
        for(j=0; j<31; j++){
            if(wrap->dias[i][j]>max){
                max = wrap->dias[i][j];
                mes = i+1;
                dia = j+1;
            }
        }
    }
    sprintf(strTotalDay, "%s/%02d/%02d", wrap->ano, mes, dia);
    return strTotalDay;
}

// Função que devolve o album mais ouvido em formato char*
char* getWrapTotalAlbum(Wrapped* wrap){
    char* strTotalAlbum = (char*)malloc(9*sizeof(char));
    int albumId = 0;
    int tempoAlbum = 0;

    for(int i = 0;wrap->albuns[0][i] != 0; i++){
        if(wrap->albuns[1][i]>tempoAlbum){
            tempoAlbum = wrap->albuns[1][i];
            albumId = wrap->albuns[0][i];
        }
    }
    sprintf(strTotalAlbum, "AL%06d", albumId);
    return strTotalAlbum;
}

// Função que devolve a hora mais ouvida do dia em formato char*
char* getWrapTotalHour(Wrapped* wrap){
    int max=0;
    int listTime=0;
    char* strTotalHour = (char*)malloc(3*sizeof(char)); 

    for(int i=0; i<24; i++){
        if(wrap->horas[i]>listTime){
            listTime = wrap->horas[i];
            max = i;
        }
    }
    sprintf(strTotalHour, "%02d", max);
    return strTotalHour;
}


// ----------------------------------------------------------------PRINT E SORT----------------------------------------------------------------

// Função para ordenar a lista de artistas por ordem decrescente de tempo de listening time
void sortWrap(Wrapped* wrap){
    
    if (wrap == NULL || wrap->artistsTimes == NULL) {
        return;  // Se a estrutura ou a lista estiverem vazias, não faz nada
    }

    struct artistsTimes* sorted = NULL;  // Lista ordenada
    struct artistsTimes* current = wrap->artistsTimes;  // Nó atual

    while (current != NULL) {
        struct artistsTimes* next = current->next;
        // Inserir o nó atual na lista ordenada
        if (sorted == NULL || sorted->listTime < current->listTime) {
            // Inserir no início da lista ordenada
            current->next = sorted;
            sorted = current;
        } 
        else{
            struct artistsTimes* temp = sorted;
            // Procurar o local correto para inserção
            while (temp->next != NULL && temp->next->listTime >= current->listTime) {
                temp = temp->next;
            }
            // Inserir após o nó encontrado
            current->next = temp->next;
            temp->next = current;
        }
        current = next;  // Passa para o próximo nó
    }

    wrap->artistsTimes = sorted;  // Atualiza o ponteiro da lista original para a lista ordenada
}

void printWrapped(Wrapped* wrap) {
    if (wrap == NULL) {
        printf("Estrutura Wrapped nula.\n");
        return;
    }

    // Imprimir o ano e o userId
    printf("Ano: %s\n", wrap->ano ? wrap->ano : "Não disponível");
    printf("User ID: %ld\n", wrap->userId);

    // Imprimir os albuns até encontrar 0 no índice [0][x]
    printf("Álbuns: \n");
    for (int i = 0; wrap->albuns != NULL && wrap->albuns[0][i] != 0; i++) {
        printf("  Álbum %d: %d\n", wrap->albuns[0][i], wrap->albuns[1][i]);
    }

    // Imprimir as horas
    printf("Horas: \n");
    for (int i = 0; i < 24; i++) {
        printf("  Hora %d: %d\n", i, wrap->horas[i]);
    }

    // Imprimir os gêneros
    printf("Gêneros: \n");
    for (int i = 0; i < 10; i++) {
        if(i==0) printf("  Blues: %d\n", wrap->generos[i]);
        else if(i==1) printf("  Classical: %d\n", wrap->generos[i]);
        else if(i==2) printf("  Country: %d\n", wrap->generos[i]);
        else if(i==3) printf("  Electronic: %d\n", wrap->generos[i]);
        else if(i==4) printf("  Hip Hop: %d\n", wrap->generos[i]);
        else if(i==5) printf("  Jazz: %d\n", wrap->generos[i]);
        else if(i==6) printf("  Metal: %d\n", wrap->generos[i]);
        else if(i==7) printf("  Pop: %d\n", wrap->generos[i]);
        else if(i==8) printf("  Reggae: %d\n", wrap->generos[i]);
        else if(i==9) printf("  Rock: %d\n", wrap->generos[i]);
    }

    // Imprimir os dias [12][31]
    printf("Dias: \n");
    for (int i = 0; i < 12; i++) {
        printf("  Mês %d:\n", i + 1);
        for (int j = 0; j < 31; j++) {
            if (wrap->dias[i][j] != 0) {
                printf("    Dia %d: %d\n", j+1, wrap->dias[i][j]);
            }
        }
    }

    // Imprimir os artistas
    printf("Artistas: \n");
    ArtistsTimes* current = wrap->artistsTimes;
    while (current != NULL) {
        printf("  Artista ID(s): ");
        for (int i = 0; current->artistId[i] != 0; i++) {
            printf("%ld ", current->artistId[i]);
        }
        printf("\n");

        printf("  Tempo: %d\n", current->listTime);

        printf("  Música(s): ");
        for (int i = 0; current->listMus[i] != 0; i++) {
            printf("%ld ", current->listMus[i]);
        }
        printf("\n\n");

        current = current->next;
    }
}