# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/15 11:16:48 by gponcele          #+#    #+#              #
#    Updated: 2022/11/15 11:29:02 by gponcele         ###   ########.fr        #
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

NAME						=	minishell


# Files

SRC							=	src/main.c

SRC_LINUX					=	src/main.c libft/ft_strlen.c libft/ft_strnstr.c libft/ft_strncmp.c

LIBFT						=	./libft/libft.a

INC							=	-I./inc


# Flags

CFLAGS						=	-Wall -Wextra -Werror

RM							=	rm -rf

CC							=	gcc


# Rules

all: 		$(NAME)

linux:		
					$(CC) $(CFLAGS) $(INC) $(SRC_LINUX) -o $(NAME)

$(NAME):
					@$(CC) $(CFLAGS) $(INC) $(SRC) -o $(NAME)
					@echo "$(GREEN)********** Compiled. $(RESET)"

clean:
					@$(RM) $(OBJS)
					@echo "$(PURPLE)********* Objects removed. $(RESET)"

fclean: clean
			@$(RM) $(NAME)
			@echo "$(LIGHTPURPLE)********* Executable removed. $(RESET)"

re: fclean all

.PHONY: all clean fclean re