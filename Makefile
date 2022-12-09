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
LIBFT = libft/libft.a
FLAGS = -Wall -Wextra -Werror

SERVER_SOURCE = server.c
SERVER_OBJECT = $(SERVER_SOURCE:%.c=%.o)

CLIENT_SOURCE = client.c
CLIENT_OBJECT = $(CLIENT_SOURCE:%.c=%.o)

all : $(NAME)

$(NAME) : server client

server : $(SERVER_OBJECT) $(LIBFT)
	cc -o server $(FLAGS) $(SERVER_OBJECT) $(LIBFT)

client : $(CLIENT_OBJECT) $(LIBFT)
	cc -o client $(FLAGS) $(CLIENT_OBJECT) $(LIBFT)

$(LIBFT) :
	make -C libft

%.o : %.c
	cc -c $(FLAGS) $^

clean :
	make -C libft clean
	rm -f $(SERVER_OBJECT) $(CLIENT_OBJECT)

fclean : clean
	make -C libft fclean
	rm -f server client

re : fclean all