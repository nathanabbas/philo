# =============================================================================
#  philo_bonus – Makefile (bonus part, named semaphores version)
# =============================================================================

NAME      := philo_bonus
CC        := cc
CFLAGS    := -Wall -Wextra -Werror
THREADS   := -pthread
INC       := -Iinc
SRCDIR    := src
HDRS      := inc/philo_bonus.h

SRC := \
	$(SRCDIR)/args_bonus.c \
	$(SRCDIR)/actions_bonus.c \
	$(SRCDIR)/cleanup_bonus.c \
	$(SRCDIR)/init_bonus.c \
	$(SRCDIR)/main_bonus.c \
	$(SRCDIR)/monitor_bonus.c \
	$(SRCDIR)/routine_bonus.c \
	$(SRCDIR)/time_bonus.c \
	$(SRCDIR)/utils_bonus.c \
	$(SRCDIR)/print_bonus.c

OBJ := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(HDRS)
	$(CC) $(CFLAGS) $(OBJ) $(THREADS) -o $@

$(SRCDIR)/%.o: $(SRCDIR)/%.c $(HDRS)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
