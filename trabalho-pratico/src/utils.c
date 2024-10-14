#include "utils.h"

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

// função que verifica se toda a string é composta por dígitos
int strDigit(char *str){
    
    if(!str){
        return 1;
    }

    while(*str){
        if(!isdigit(*str)){
            return 1;
        }
        str++;
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

    for(int i=0;user[i]!='\0';i++){
        if(!isdigit(user[i]) && !isalpha(user[i])) return 1;
    }
    if(nameVerify(lDomain) == 1) return 1;
    if(nameVerify(rDomain) == 1 || strlen(rDomain)<=1 || strlen(rDomain)>=4) return 1;    
    
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

    if((strDigit(ano) || strDigit(mes) || strDigit(dia)) != 0) return 1;
    
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
int verify_music(char* duration){
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