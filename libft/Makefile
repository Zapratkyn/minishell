# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/15 11:16:48 by gponcele          #+#    #+#              #
#    Updated: 2022/11/24 10:44:55 by ademurge         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME						=	libft.a
SRC							=	ft_calloc.c \
								ft_insert.c \
								ft_isalnum.c \
								ft_putstr_fd.c \
								ft_split.c \
								ft_strchr.c \
								ft_strcmp.c \
								ft_strdup.c \
								ft_strjoin.c \
								ft_strlcpy.c \
								ft_strlen.c \
								ft_strncmp.c \
								ft_strnstr.c \
								ft_substr.c \
								ft_usleep.c

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