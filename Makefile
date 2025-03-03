# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/25 11:38:47 by gaducurt          #+#    #+#              #
#    Updated: 2025/03/03 13:05:49 by gaducurt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_SERV = server
NAME_CLT = client

CC = cc

CFLAGS = -Wall -Wextra -Werror -MMD -MP -I$(INCLUDE) -g3

INCLUDE = inc
			
BIN = bin/

DIR_SERV = src_server/

DIR_CLT = src_client/

SRC_SERV = 	server.c			\
			server_utils.c		\
			
SRC_CLT =	client.c		\
			client_utils.c	\

LIBS = Libft/libft.a

OBJ_SERV = $(addprefix $(BIN), $(SRC_SERV:.c=.o))
DEPS_SERV =   $(OBJ_SERV:.o=.d)

OBJ_CLT = $(addprefix $(BIN), $(SRC_CLT:.c=.o))
DEPS_CLT = $(OBJ_CLT:.o=.d)

all: $(BIN) libft $(NAME_SERV) $(NAME_CLT)

libft:
	$(MAKE) -C Libft

$(NAME_SERV): $(OBJ_SERV) $(LIBS)
	$(CC) $(CFLAGS) -o $(NAME_SERV) $(OBJ_SERV) $(LIBS)

$(NAME_CLT): $(OBJ_CLT) $(LIBS)
	$(CC) $(CFLAGS) -o $(NAME_CLT) $(OBJ_CLT) $(LIBS)

$(BIN)%.o: $(DIR_SERV)%.c | $(BIN)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN)%.o: $(DIR_CLT)%.c | $(BIN)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN):
	mkdir -p $(BIN)

%.o : %.c Makefile $(LIBS)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	$(MAKE) clean -C Libft
	rm -rf $(BIN) Libft/fclean

fclean: clean
	rm -f $(NAME_SERV) $(NAME_CLT) Libft/libft.a

re: fclean all

.PHONY: all clean fclean re libft

-include $(DEPS_CLT) $(DEPS_SERV)
