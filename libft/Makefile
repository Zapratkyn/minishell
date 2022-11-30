# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/15 11:16:48 by gponcele          #+#    #+#              #
#    Updated: 2022/11/30 18:21:40 by ademurge         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME						=	libft.a
SRC							=	lst/ft_lst_index.c \
								lst/ft_lst_to_str.c \
								lst/ft_lstadd_back.c \
								lst/ft_lstclear.c \
								lst/ft_lstdelone.c \
								lst/ft_lstdup.c \
								lst/ft_lstget.c \
								lst/ft_lstlast.c \
								lst/ft_lstnew.c \
								lst/ft_lstsize.c \
								lst/ft_sortlst.c \
								ft_calloc.c \
								ft_find_index.c \
								ft_insert.c \
								ft_isalnum.c \
								ft_itoa.c \
								ft_n_putstr.c \
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
								ft_itoa.c

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