#ifndef MUSIC_H
#define MUSIC_H

// Forma de enunciar a entidade música.
typedef struct music Music;

// Função para criar uma estrutura da entidade música parametrizada.
Music* createMusic(int id, char* title, int* artist_id, int num_artists, char* duration, char* genre, int year, char* lyrics);

// Função de verificação da validade de uma musica
int musicLineVerify(char *line);

// GETTERS
int* getMusicID(Music* m);
char* getMusicTitle(Music* m);
int* getMusicArtistIDs(Music* m);
int getMusicNumArtists(Music* m);
char* getMusicDuration(Music* m);
char* getMusicGenre(Music* m);
int getMusicYear(Music* m);
char* getMusicLyrics(Music* m);

// SETTERS
void setMusicID(Music* m, int newID);
void setMusicTitle(Music* m, char* newTitle);
void setMusicArtistIDs(Music* m, int* newArtistID, int newNumArtists);
void setMusicDuration(Music* m, char* newDuration);
void setMusicGenre(Music* m, char* newGenre);
void setMusicYear(Music* m, int newYear);
void setMusicLyrics(Music* m, char* newLyrics);

// Função para libertar a memória de uma entidade do tipo música.
void freeMusic(Music* music);

#endif