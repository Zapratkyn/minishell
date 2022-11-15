# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/15 11:16:48 by gponcele          #+#    #+#              #
#    Updated: 2022/11/15 17:23:43 by ademurge         ###   ########.fr        #
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

INC							=	-I./inc


# Flags

CFLAGS						=	-Wall -Wextra -Werror -lreadline

RM							=	rm -rf

CC							=	gcc


# Rules

all: 		$(NAME)

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