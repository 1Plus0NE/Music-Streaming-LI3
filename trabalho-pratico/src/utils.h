#ifndef UTILS_H
#define UTILS_H

//funções de manipulação de strings
char* remove_aspas(char* str);

//funções de validação
int strDigit(char *str);

int nameVerify(char *name);

int emailVerify(char *email);

int birthDateVerify(char* birth_date);

int verify_music(char* duration);

int verify_year(int year);

int verifyLikedMusics(char* liked_musics_str, MusicTable* music_table);

//funções de conversão
int calculaIdade(char* birthdate);