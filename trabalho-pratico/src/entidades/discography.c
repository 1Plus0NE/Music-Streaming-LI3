#include "../../include/entidades/discography.h"

struct discography {
    long int id; // Id do artista/banda
    char* name;
    char* country;
    int duration; // Duracao em segundos
    ArtistType type;
    struct discography* next;
};

// Função para ordenar a discografia por durações, e por ordem crescente de id, se necessário
void sortByDuration(Discography** head){
    if (*head == NULL || (*head)->next == NULL) {
        // Lista vazia ou com um único elemento não precisa de ordenação
        return;
    }

    int swapped;
    Discography *ptr1;
    Discography *lptr = NULL;

    // While dentro de um do-while para simplificar verificação a 1 função
    do{
        swapped = 0;
        ptr1 = *head;

        while (ptr1->next != lptr){
            // Duraçõess decrescentes || em caso de durações iguais, ordena por ordem crescente de id
            if (ptr1->duration < ptr1->next->duration || (ptr1->duration == ptr1->next->duration && ptr1->id > ptr1->next->id)){

                // Troca os dados dos artistas
                long int tempId = ptr1->id;
                char* tempName = ptr1->name;
                char* tempCountry = ptr1->country;
                int tempDuration = ptr1->duration;
                ArtistType tempType = ptr1->type;

                // Efetua a troca
                ptr1->id = ptr1->next->id;
                ptr1->name = ptr1->next->name;
                ptr1->country = ptr1->next->country;
                ptr1->duration = ptr1->next->duration;
                ptr1->type = ptr1->next->type;

                ptr1->next->id = tempId;
                ptr1->next->name = tempName;
                ptr1->next->country = tempCountry;
                ptr1->next->duration = tempDuration;
                ptr1->next->type = tempType;

                swapped = 1; // Indica que uma troca ocorreu
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1; // O último elemento já está ordenado
    } while (swapped);
}


// Função para incrementar em segundos, a duração da discografia de um artista
void durationAdd(Discography* disco, const char* duration, long int id){
    
    // Converter a string de duração em segundos sem atoi
    int h=0, m=0, s=0;
    printf("%s\n", duration);
    if (sscanf(duration, "%d:%d:%d", &h, &m, &s) != 3){
        // Em principio nunca acontece
        printf("Formato de duração inválido.\n");
        return;
    }

    int seconds = h*3600 + m*60 + s; // Calcula o total em segundos

    // Percorre a lista para encontrar o artista
    Discography* newDisco = disco;
    while (newDisco != NULL) {
        if (newDisco->id == id){
            newDisco->duration += seconds;
            break;
        }
        newDisco = newDisco->next; // Caso ainda não tenha encontrado o id respetivo
    }

    // Em principio nunca acontece, não é suposto se os dados são validos
    if(newDisco == NULL) printf("Artista com ID %ld não encontrado.\n", id);
}

//função para libertar a memória da estrutura discografia.
void freeDiscography(Discography* disco){
    Discography* currentDisco = disco;
    Discography* nextDisco;

    while (currentDisco != NULL) {
        nextDisco = currentDisco->next;
        free(currentDisco->name);
        free(currentDisco->country);
        free(currentDisco);
        currentDisco = nextDisco;
    }
}

// Função que adiciona artista por artista numa lista ligada, ignorando a ordem 
void artistInsert(Discography** disco, long int id, const char* name, const char* country, ArtistType type){
    // Atribuição dos valores do novo artista a uma nova lista
    Discography* newDisco = (Discography*)malloc(sizeof(Discography));
    if (!newDisco) {
        perror("Erro ao alocar memória para o novo artista.\n");
        exit(EXIT_FAILURE);
    }
    newDisco->id = id;
    newDisco->name = strdup(name);
    newDisco->country = strdup(country);
    newDisco->duration = 0; // Duração sempre 0
    newDisco->type = type;
    newDisco->next = *disco;
    
    *disco = newDisco; // Atualização da lista
}

//getters e setters de discografia.
long int* getDiscographyId(Discography* d){
    return d ? &(d -> id) : NULL;
}

char* getDiscographyName(Discography* d){
    return d -> name ? strdup(d -> name) : NULL;
}

char* getDiscographyCountry(Discography* d){
    return d -> country ? strdup(d -> country) : NULL;
}

int getDiscographyDuration(Discography* d){
    return d ? d -> duration : 0;
}

ArtistType getDiscographyType(Discography* d){
    return d ? d -> type : (ArtistType)0;
}

Discography* getDiscographyNext(Discography* d){
    return d ? d -> next : NULL;
}

void setDiscographyId(Discography* d, long int id){
    if (d) d -> id = id;
}

void setDiscographyName(Discography* d, char* name){
    if(d){
        if(d -> name){
            free(d -> name);
        }
        d -> name = strdup(name);
    }
}

void setDiscographyCountry(Discography* d, char* country){
    if(d){
        if(d -> country){
            free(d -> country);
        }
        d -> country = strdup(country);
    }
}

void setDiscographyDuration(Discography* d, int duration){
    if(d){
        d -> duration = duration;
    }
}

void setDiscographyType(Discography* d, ArtistType type){
    if(d){
        d -> type = type;
    }
}

void setDiscographyNext(Discography* d, Discography* next){
    if(d){
        d -> next = next;
    }
}