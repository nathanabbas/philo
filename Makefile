# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/22 16:41:24 by nabbas            #+#    #+#              #
#    Updated: 2025/05/22 16:41:25 by nabbas           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/15 09:00:00 by nabbas            #+#    #+#              #
#   Updated: 2025/05/22 15:20:00 by nabbas           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = philo

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -pthread
INC     = -Iincludes

SRC_DIR = src
SRCS    = $(SRC_DIR)/main.c \
          $(SRC_DIR)/init.c \
          $(SRC_DIR)/routine.c \
          $(SRC_DIR)/monitor.c \
          $(SRC_DIR)/log.c \
          $(SRC_DIR)/utils_time.c \
          $(SRC_DIR)/utils_parse.c \
          $(SRC_DIR)/cleanup.c \
          $(SRC_DIR)/waiter.c

OBJS    = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INC) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
