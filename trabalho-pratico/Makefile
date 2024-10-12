#Nome do executável
PRINCIPAL = programa-principal
INTERATIVO = programa-interativo
TESTES = programa-testes

#Compilador
CC = gcc

#Flags
CFLAGS = -Wall -Wextra -std=c11 -g

#Diretorias
SRC_DIR = src
ENTIDADES_DIR = $(SRC_DIR)/entidades
GESTORES_DIR = $(SRC_DIR)/gestores
PARSER_DIR = $(SRC_DIR)/parser
QUERIES_DIR = $(SRC_DIR)/queries

ENTIDADES_SRC = $(ENTIDADES_DIR)/artist.c $(ENTIDADES_DIR)/music.c $(ENTIDADES_DIR)/user.c
GESTORES_SRC = $(GESTORES_DIR)/gestor_artist.c $(GESTORES_DIR)/gestor_music.c $(GESTORES_DIR)/gestor_user.c
PARSER_SRC = $(PARSER_DIR)/parser.c
QUERIES_SRC = $(QUERIES_DIR)/queries.c
UTILS_SRC = $(SRC_DIR)/utils.c
MAIN_SRC = $(SRC_DIR)/main.c

SRC_PRINCIPAL = $(ENTIDADES_SRC) $(GESTORES_SRC) $(PARSER_SRC) $(QUERIES_SRC) $(UTILS_SRC) $(MAIN_SRC)

OBJ_PRINCIPAL = $(SRC_PRINCIPAL:.c=.o)

INCLUDE_DIR = $(SRC_DIR)

#Compilar todos os execs
all: $(PRINCIPAL)

#Criação do exec principal
$(PRINCIPAL): $(OBJ_PRINCIPAL)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -o $(PRINCIPAL) $(OBJ_PRINCIPAL)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

#Limpar os objetos e os execs
clean:
	rm -f $(OBJ_PRINCIPAL) $(PRINCIPAL)