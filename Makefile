# Nom de l'exécutable
NAME = pipex

# Compilateur et flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Fichiers sources et objets
SRCS = src/pipex.c src/get_path.c src/pipe_utils.c src/child_process.c src/exec_cmd.c src/cleanup.c src/ft_split.c
OBJS = $(SRCS:.c=.o)

# Dépendances
INCLUDE = -I includes

# Commandes
RM = rm -f

# Règle principale
all: $(NAME)

# Compilation des fichiers objets
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

# Compilation finale
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) -o $(NAME)

# Nettoyage des fichiers objets
clean:
	$(RM) $(OBJS)

# Nettoyage complet
fclean: clean
	$(RM) $(NAME)

# Recompile tout
re: fclean all

# Évite que Make interprète clean, fclean et re comme des fichiers
.PHONY: all clean fclean re
