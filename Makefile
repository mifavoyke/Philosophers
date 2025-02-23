NAME := philo
DIR_SRC := ./philo
DIR_BIN := ./bin
CC := gcc
CFLAGS := -Wall -Wextra -Werror -g
RM := rm -f

SRC :=  $(DIR_SRC)/forks.c \
        $(DIR_SRC)/threads.c \
        $(DIR_SRC)/supervisor.c \
        $(DIR_SRC)/ft_atoi.c \
        $(DIR_SRC)/philo.c \
        $(DIR_SRC)/routine.c \
        $(DIR_SRC)/utils.c \
        $(DIR_SRC)/given.c \
        $(DIR_SRC)/eating.c

OBJS := $(SRC:.c=.o)

all: $(DIR_BIN)/$(NAME)

$(DIR_BIN)/$(NAME): $(OBJS)
	mkdir -p $(DIR_BIN)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) -r $(DIR_BIN)

re: fclean all

.PHONY: all clean fclean re