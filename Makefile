NAME		= philo
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
THREADS		= -pthread
INC			= -Iinc
SRCDIR		= src
HDRS		= inc/philo.h

SRCDIR  = src
SRC     = $(SRCDIR)/args.c \
          $(SRCDIR)/cleanup.c \
          $(SRCDIR)/init.c \
          $(SRCDIR)/main.c \
          $(SRCDIR)/monitor.c \
          $(SRCDIR)/print.c \
          $(SRCDIR)/routine.c \
          $(SRCDIR)/actions.c \
          $(SRCDIR)/time.c \
          $(SRCDIR)/utils.c


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

