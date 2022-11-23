# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/15 11:16:48 by gponcele          #+#    #+#              #
#    Updated: 2022/11/23 11:15:16 by gponcele         ###   ########.fr        #
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

SRC							=	src/main.c src/ft_env.c src/minishell_utils.c src/ft_free.c src/get_cmd.c src/ft_split_cmd.c

LIBFT						=	./libft/libft.a

LIBFT_LINUX					=	libft/ft_strlen.c libft/ft_strnstr.c libft/ft_strncmp.c libft/ft_strdup.c libft/ft_strjoin.c \
								libft/ft_isalnum.c libft/ft_strchr.c

INC							=	-I./inc


# Flags

CFLAGS						=	-Wall -Wextra -Werror

RM							=	rm -rf

CC							=	gcc


# Rules

all: 		$(NAME)

linux:		
					@$(CC) $(CFLAGS) $(INC) $(SRC) $(LIBFT_LINUX) -lreadline -o $(NAME)
					@echo "$(GREEN)********** Compiled. $(RESET)"

$(NAME):
					@$(CC) $(CFLAGS) $(INC) $(SRC) $(LIBFT) -lreadline -o $(NAME)
					@echo "$(GREEN)********** Compiled. $(RESET)"

clean:
					@$(RM) $(OBJS)
					@echo "$(PURPLE)********* Objects removed. $(RESET)"

fclean: clean
			@$(RM) $(NAME)
			@echo "$(LIGHTPURPLE)********* Executable removed. $(RESET)"

re: fclean all

.PHONY: all clean fclean re