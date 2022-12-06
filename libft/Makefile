# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/15 11:16:48 by gponcele          #+#    #+#              #
#    Updated: 2022/12/06 13:36:55 by ademurge         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors

BLACK		= $(shell tput -Txterm setaf 0)
RED			= $(shell tput -Txterm setaf 1)
GREEN		= $(shell tput -Txterm setaf 2)
YELLOW		= $(shell tput -Txterm setaf 3)
LIGHTPURPLE	= $(shell tput -Txterm setaf 4)
PURPLE		= $(shell tput -Txterm setaf 5)
BLUE		= $(shell tput -Txterm setaf 6)
WHITE		= $(shell tput -Txterm setaf 7)
RESET		= $(shell tput -Txterm sgr0)


# Name of the executable

NAME						=	libft.a


# Files

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
								ft_put_tab.c \
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
								ft_itoa.c \
								ft_tablen.c


# Flags

CC							=	gcc
RM							=	rm -rf
INCLUDES					=	-I./includes
CFLAGS						=	-Wall -Wextra -Werror
OBJS						=	$(SRC:.c=.o)


# Rules


%o:				%c
				@gcc ${CFLAGS} -I./includes -c $< -o ${<:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
			@ar -rcs $@ $^
			@echo "$(RED)********** Libft compiled. $(RESET)"

clean:
			@$(RM) $(OBJS)
#			@echo "$(YELLOW)********** Libft objects removed. $(RESET)"

fclean: clean
			@$(RM) $(NAME)
#			@echo "$(YELLOW)********** Libft executable removed. $(RESET)"

re: fclean all

.PHONY: all clean fclean re