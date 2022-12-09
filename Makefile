# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rburgsta <rburgsta@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/12 09:54:03 by rburgsta          #+#    #+#              #
#    Updated: 2022/10/12 09:54:03 by rburgsta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk

FT_PATH = libft
LIBFT_INC = $(FT_PATH)
FLAGS = -Wall -Wextra -Werror

SERVER_SOURCE = server.c
SERVER_OBJECT = $(SERVER_SOURCE:%.c=%.o)

CLIENT_SOURCE = client.c
CLIENT_OBJECT = $(CLIENT_SOURCE:%.c=%.o)

all : $(NAME)

$(NAME) : $(FT_PATH) server client

server : $(SERVER_OBJECT)
	make -C $(FT_PATH)
	cc -o server $(FLAGS) $(SERVER_OBJECT) -L$(FT_PATH) -lft

client : $(CLIENT_OBJECT)
	make -C $(FT_PATH)
	cc -o client $(FLAGS) $(CLIENT_OBJECT) -L$(FT_PATH) -lft

$(FT_PATH) :
	git clone git@github.com:PythonGermany/42_libft.git $(FT_PATH)

%.o: %.c
	cc -c $(FLAGS) -I$(LIBFT_INC) $^ 

clean :
	rm -f $(OBJ)

fclean: clean
	rm -rf server client  $(SERVER_OBJECT) $(CLIENT_OBJECT) $(FT_PATH)

re: fclean all
