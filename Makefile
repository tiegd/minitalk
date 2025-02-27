# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/25 11:38:47 by gaducurt          #+#    #+#              #
#    Updated: 2025/02/27 13:10:24 by gaducurt         ###   ########.fr        #
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

DIR_PRINTF = ft_printf/

SRC_SERV = 	server.c			\
			server_utils.c		\
			
SRC_CLT =	client.c		\
			client_utils.c	\

SRC_PRINTF =	ft_printf.c	\
				ft_putchar.c	\
				ft_putnbr_base.c	\
				ft_putnbr_unsigned.c	\
				ft_putnbr.c	\
				ft_putptr.c	\
				ft_putstr.c	\
				ft_strlen.c	\

LIBS = Libft/libft.a

OBJ_SERV = $(addprefix $(BIN), $(SRC_SERV:.c=.o))
DEPS_SERV =   $(OBJ_SERV:.o=.d)

OBJ_CLT = $(addprefix $(BIN), $(SRC_CLT:.c=.o))
DEPS_CLT = $(OBJ_CLT:.o=.d)

OBJ_PRINTF = $(addprefix $(BIN), $(SRC_PRINTF:.c=.o))
DEPS_PRINTF = $(OBJ_PRINTF:.o=.d)

all: libft $(BIN) $(NAME_SERV) $(NAME_CLT)

libft:
	$(MAKE) -C Libft

$(NAME_SERV): $(OBJ_SERV) $(OBJ_PRINTF)
	$(CC) $(CFLAGS) -o $(NAME_SERV) $(OBJ_SERV) $(OBJ_PRINTF) $(LIBS)

$(NAME_CLT): $(OBJ_CLT) $(OBJ_PRINTF)
	$(CC) $(CFLAGS) -o $(NAME_CLT) $(OBJ_CLT) $(OBJ_PRINTF) $(LIBS)

$(BIN)%.o: $(DIR_SERV)%.c | $(BIN)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN)%.o: $(DIR_CLT)%.c | $(BIN)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN)%.o: $(DIR_PRINTF)%.c | $(BIN)
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

-include $(DEPS_CLT) $(DEPS_SERV) $(DEPS_PRINTF)
