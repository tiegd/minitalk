# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/25 11:38:47 by gaducurt          #+#    #+#              #
#    Updated: 2025/02/25 15:43:22 by gaducurt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_SERV = server
NAME_CLT = client

CC = cc

CFLAGS = -Wall -Wextra -Werror

HEADER = 	Libft/libft.h	\
			minitalk.h
			
OBJDIR = obj

SRC_SERV = 	server.c			\
			server_utils.c		\
			
SRC_CLT =	client.c		\
			client_utils.c	\

LIBS = Libft/libft.a

OBJ = $(patsubst %.c, $(OBJDIR)/%.o, $(SRC))

all: libft $(NAME_SERV) $(NAME_CLT)

libft:
	$(MAKE) -C Libft

$(NAME_SERV): $(OBJ) $(HEADER) $(LIBS)
	$(CC) $(CFLAGS) -o $(NAME_SERV) $(OBJ) $(LIBS)

$(NAME_CLT): $(OBJ) $(HEADER) $(LIBS)
	$(CC) $(CFLAGS) -o $(NAME_CLT) $(OBJ) $(LIBS)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

%.o : %.c Makefile $(LIBS)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	$(MAKE) clean -C Libft
	rm -rf $(OBJ) Libft/fclean
fclean: clean
	rm -rf $(NAME) Libft/libft.a $(OBJDIR)
re: fclean all

.PHONY: all clean fclean re libft