#include "../include/utils.h"

#define MAX_MUSICS 1000

//função responsável por remover as aspas.
char* remove_aspas(char* str) {
    if (!str) return NULL;  // Verifica se a string é nula
    
    int len = strlen(str);
    if (len == 0) return str;  // Se a string for vazia, retorne-a diretamente
    
    // Se a string começa e termina com aspas, remova-as
    if (str[0] == '"' && str[len - 1] == '"') {
        str[len - 1] = '\0';  // Remove a última aspas
        return str + 1;       // Retorna a string sem a primeira aspas
    }
    
    return str;  // Retorna a string sem alterações se não houver aspas
}

// Função que remove espaços de uma dada string
char* remove_espacos(char* input){
    int i,j;
    char *output=input;
    for (i = 0, j = 0; i<strlen(input); i++,j++){
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

    // Testar com  casos práticos a divisao por tokens
    char *user = strsep(&email, "@");
    char *lDomain = strsep(&email, ".");
    char *rDomain = strsep(&email, "\0");
    if(!user || !lDomain || !rDomain) return 1;

    if(strlen(user)<1) return 1;
    for(int i=0;user[i]!='\0';i++){
        if(isdigit(user[i])==0 && isalpha(user[i])==0) return 1;
    }
    if(nameVerify(lDomain) != 0 || strlen(lDomain)<1) return 1;
    if(nameVerify(rDomain) != 0 || strlen(rDomain)<2 || strlen(rDomain)>3) return 1;    
    
    return 0;
}

// função que valida uma data de nascimento mediante os requerimentos.
int birthDateVerify(char* birth_date){
    // data base 2024/09/09

    if(!birth_date){
        return 1;
    }

    if(birth_date[4] != '/' || birth_date[7] != '/' || birth_date[10] != '\0') return 1;

    char *ano = strsep(&birth_date, "/");
    char *mes = strsep(&birth_date, "/");
    char *dia = strsep(&birth_date, "\0");

    if(strDigit(ano)!=0 || strDigit(mes)!=0 || strDigit(dia)!=0) return 1;
    
    // Data numérica verificada, transformar em int
    int anoInt = atoi(ano);
    int mesInt = atoi(mes);
    int diaInt = atoi(dia);

    // Verificação lógica
    if(anoInt>2024 || (anoInt==2024 && mesInt>9) || (anoInt==2024 && mesInt==9 && diaInt>9)) return 1;
    else if(anoInt<0) return 1;
    else if(mesInt<=0 || mesInt>12) return 1;
    else if(diaInt<=0 || diaInt>31) return 1;
    else return 0;
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
    
    // Remover os parentesis retos
    input_copy++;
    input_copy[strlen(input_copy) - 1] = '\0';

    // Verificar se está empty
    if(strlen(input_copy) == 0){
        *count = 0;
        free(input_copy - 1);
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

    free(input_copy);  // Libertamos a memoria do pointer original
    
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

//função que passa uma string do tipo do artista para o enum type
ArtistType stringToArtistType(char* type_str){
    if(strcmp(type_str, "individual") == 0){
        return INDIVIDUAL;
    }else if(strcmp(type_str, "grupo") == 0){
        return GRUPO;
    }else{
        fprintf(stderr, "tipo de artista inexistente %s.\n", type_str);
        exit(EXIT_FAILURE);
    }
}