NAME        = philo_bonus
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
THREADS     = -pthread
INC         = -Iinc
SRCDIR      = src

SRC         = $(SRCDIR)/args_bonus.c \
              $(SRCDIR)/actions_bonus.c \
              $(SRCDIR)/cleanup_bonus.c \
              $(SRCDIR)/init_bonus.c \
              $(SRCDIR)/main_bonus.c \
              $(SRCDIR)/monitor_bonus.c \
              $(SRCDIR)/routine_bonus.c \
              $(SRCDIR)/time_bonus.c \
              $(SRCDIR)/utils_bonus.c \
              $(SRCDIR)/print_bonus.c

OBJ         = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(THREADS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
