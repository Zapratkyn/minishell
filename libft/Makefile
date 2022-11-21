# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/15 11:16:48 by gponcele          #+#    #+#              #
#    Updated: 2022/11/21 11:45:13 by gponcele         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME						=	libft.a
SRC							=	ft_strlen.c ft_strnstr.c ft_strncmp.c ft_strdup.c ft_strjoin.c	
CC							=	gcc
RM							=	rm -rf
INCLUDES					=	-I./includes
CFLAGS						=	-Wall -Wextra -Werror
OBJS						=	$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
			ar rcs $(NAME) $(OBJS)

clean:
			$(RM) $(OBJS)

fclean: clean
			$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re