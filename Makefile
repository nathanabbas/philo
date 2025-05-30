NAME		= philo
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
THREADS		= -pthread
INC			= -Iinc
SRCDIR		= src
HDRS		= inc/philo.h
SRC			= $(wildcard $(SRCDIR)/*.c)
OBJ			= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(HDRS)
	$(CC) $(CFLAGS) $(OBJ) $(THREADS) -o $(NAME)

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
