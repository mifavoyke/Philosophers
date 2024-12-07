NAME = philo
DIR_SRC = ./philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -rf

SRC = $(DIR_SRC)/philo.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(DIR_SRC)/%.o: $(DIR_SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re