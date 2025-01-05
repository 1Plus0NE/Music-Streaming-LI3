# Nome do exec
PRINCIPAL = programa-principal
INTERATIVO = programa-interativo
TESTES = programa-testes

CC = gcc

CFLAGS = -Wall -Wextra -std=gnu11 -g `pkg-config --cflags glib-2.0`

# Diretorias
SRC_DIR = src
ESTATISTICAS_DIR = $(SRC_DIR)/estatisticas
ENTIDADES_DIR = $(SRC_DIR)/entidades
GESTORES_DIR = $(SRC_DIR)/gestores
PARSER_DIR = $(SRC_DIR)/parser
OTHER_DIR = $(SRC_DIR)

# Diretorias dos headers
ESTATISTICAS_INCLUDE_DIR = $(INCLUDE_DIR)/estatisticas
ENTIDADES_INCLUDE_DIR = $(INCLUDE_DIR)/entidades
GESTORES_INCLUDE_DIR = $(INCLUDE_DIR)/gestores
PARSER_INCLUDE_DIR = $(INCLUDE_DIR)/parser
OTHER_DIR = $(INCLUDE_DIR)

ESTATISTICAS_SRC = $(ESTATISTICAS_DIR)/user_likes.c $(ESTATISTICAS_DIR)/genres_listened.c
ENTIDADES_SRC = $(ENTIDADES_DIR)/artist.c $(ENTIDADES_DIR)/music.c $(ENTIDADES_DIR)/user.c $(ENTIDADES_DIR)/discography.c $(ENTIDADES_DIR)/history.c $(ENTIDADES_DIR)/album.c $(ENTIDADES_DIR)/wrapped.c
GESTORES_SRC = $(GESTORES_DIR)/gestor_artist.c $(GESTORES_DIR)/gestor_music.c $(GESTORES_DIR)/gestor_user.c $(GESTORES_DIR)/gestor_album.c $(GESTORES_DIR)/gestor_history.c
PARSER = $(PARSER_DIR)/parser_artist.c $(PARSER_DIR)/parser_music.c $(PARSER_DIR)/parser_user.c $(PARSER_DIR)/parser_album.c $(PARSER_DIR)/parser_history.c $(PARSER_DIR)/parser.c
QUERIES = $(SRC_DIR)/queries.c
UTILS = $(SRC_DIR)/utils.c
WRITER = $(SRC_DIR)/writer.c
MAIN = $(SRC_DIR)/main.c
TESTES_SRC = $(SRC_DIR)/programa-testes.c

SRC_PRINCIPAL = $(ESTATISTICAS_SRC) $(ENTIDADES_SRC) $(GESTORES_SRC) $(PARSER) $(QUERIES) $(UTILS) $(WRITER) $(MAIN) 
SRC_TESTES = $(ESTATISTICAS_SRC) $(ENTIDADES_SRC) $(GESTORES_SRC) $(PARSER) $(QUERIES) $(UTILS) $(WRITER) $(TESTES_SRC)

OBJ_PRINCIPAL = $(SRC_PRINCIPAL:.c=.o)
OBJ_TESTES = $(SRC_TESTES:.c=.o)

INCLUDE_DIR = $(SRC_DIR)

# Compilar todos os execs
all: $(PRINCIPAL) $(TESTES)

# Criação do exec principal
$(PRINCIPAL): $(OBJ_PRINCIPAL)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -I$(ESTATISTICAS_INCLUDE_DIR) -I$(ENTIDADES_INCLUDE_DIR) -I$(GESTORES_INCLUDE_DIR) -o $(PRINCIPAL) $(OBJ_PRINCIPAL) `pkg-config --libs glib-2.0`

# Criação do exec de testes
$(TESTES): $(OBJ_TESTES)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -I$(ESTATISTICAS_INCLUDE_DIR) -I$(ENTIDADES_INCLUDE_DIR) -I$(GESTORES_INCLUDE_DIR) -o $(TESTES) $(OBJ_TESTES) `pkg-config --libs glib-2.0`

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -I$(ESTATISTICAS_INCLUDE_DIR) -I$(ENTIDADES_INCLUDE_DIR) -I$(GESTORES_INCLUDE_DIR) -c $< -o $@

# Limpar os objetos e os execs
clean:
	rm -f $(OBJ_PRINCIPAL) $(OBJ_TESTES) $(PRINCIPAL) $(TESTES)
	rm -f resultados/*