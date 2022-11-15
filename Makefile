# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/15 11:16:48 by gponcele          #+#    #+#              #
#    Updated: 2022/11/15 11:21:08 by gponcele         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME						=	minishell
SRC							=	main.c
LIBFT						=	libft/libft.a
CC							=	gcc
RM							=	rm -rf
INCLUDES					=	-I./includes
CFLAGS						=	-Wall -Wextra -Werror
OBJS						=	$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
			$(CC) $(CFLAGS) $(INCLUDES) $(LIBFT) $(SRC) -o $(NAME)

clean:
			$(RM) $(OBJS)

fclean: clean
			$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re