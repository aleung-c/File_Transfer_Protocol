#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/03/31 11:51:41 by aleung-c          #+#    #+#              #
#    Updated: 2015/03/31 11:51:42 by aleung-c         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

SERVEUR = serveur

CLIENT = client

SERVEUR_H = serveur.h

SRC_SERV = serveur.c serv_input_parsing.c serv_ls.c serv_pwd.c serv_cd.c \
serv_get.c serv_display.c serv_put.c serv_errors.c

SRC_CLIENT = client.c client_get.c client_put.c client_func.c \
client_errors.c client_init.c

OBJ_SERV = $(SRC_SERV:.c=.o)

OBJ_CLIENT = $(SRC_CLIENT:.c=.o)

LIB = ./libft/

CC = gcc -g -Wall -Werror -Wextra


all : Lib $(SERVEUR) $(CLIENT)

$(SERVEUR) : $(OBJ_SERV)
	$(CC) -o $(SERVEUR) $(OBJ_SERV) -L./libft/ -lft

$(CLIENT) : $(OBJ_CLIENT)
	$(CC) -o $(CLIENT) $(OBJ_CLIENT) -L./libft/ -lft

Lib :
	make -C $(LIB)

clean :
	rm -rf $(OBJ_SERV)
	rm -rf $(OBJ_CLIENT)
	cd $(LIB) ; make clean

fclean : clean
	rm -rf $(SERVEUR)
	rm -rf $(CLIENT)
	cd $(LIB) ; make fclean

re : fclean all

.PHONY : all clean fclean re Lib