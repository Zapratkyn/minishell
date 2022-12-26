# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/15 11:16:48 by gponcele          #+#    #+#              #
#    Updated: 2022/12/26 12:29:09 by ademurge         ###   ########.fr        #
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

SRC							=	src/builtins/builtin.c \
								src/builtins/ft_cd.c \
								src/builtins/ft_echo.c \
								src/builtins/ft_env.c \
								src/builtins/ft_exit.c \
								src/builtins/ft_export.c \
								src/builtins/ft_pwd.c \
								src/builtins/ft_unset.c \
								src/utils/builtin_utils.c \
								src/utils/exec_utils.c \
								src/utils/minishell_utils.c \
								src/utils/get_cmd_utils.c \
								src/utils/mini_heredoc_utils.c \
								src/utils/get_infos_utils.c \
								src/error.c \
								src/exec.c \
								src/main.c \
								src/free.c \
								src/get_cmd.c \
								src/get_infos.c \
								src/ft_split_cmd.c \
								src/mini_heredoc.c \
								src/ft_split_string.c \
								src/prompt_env.c \
								src/specials.c

LIBFT						=	./libft/libft.a

LIBFT_LINUX					=	libft/ft_calloc.c \
								libft/ft_find_index.c \
								libft/ft_insert.c \
								libft/ft_isalnum.c \
								libft/ft_lst_index.c \
								libft/ft_lst_to_str.c \
								libft/ft_lstadd_back.c \
								libft/ft_lstclear.c \
								libft/ft_lstdelone.c \
								libft/ft_lstget.c \
								libft/ft_lstlast.c \
								libft/ft_lstnew.c \
								libft/ft_lstsize.c \
								libft/ft_n_putstr.c \
								libft/ft_putstr_fd.c \
								libft/ft_strchr.c \
								libft/ft_strcmp.c \
								libft/ft_strdup.c \
								libft/ft_strjoin.c \
								libft/ft_strlcpy.c \
								libft/ft_strlen.c \
								libft/ft_strncmp.c \
								libft/ft_strnstr.c \
								libft/ft_substr.c \
								libft/ft_itoa.c \
								libft/ft_tablen.c

INC							=	-I./inc/.

OBJS						=	$(SRC:.c=.o)

# Flags

CFLAGS						=	-Wall -Wextra -Werror

RM							=	rm -rf

CC							=	gcc


# Rules

all: 		libft $(NAME)

%o:				%c
				@$(CC) ${CFLAGS} -I/Users/$(USER)/.brew/opt/readline/include -I./includes -c $< -o ${<:.c=.o}

linux:
					@$(CC) $(CFLAGS) $(INC) $(SRC) $(LIBFT_LINUX) -lreadline -o $(NAME)
					@echo "$(GREEN)********** Compiled. $(RESET)"

$(NAME): $(OBJS)
					@$(CC) $(CFLAGS) $(INC) $(OBJS) $(LIBFT)  -lreadline -L/Users/$(USER)/.brew/opt/readline/lib -I/Users/$(USER)/.brew/opt/readline/include -o $(NAME)
					@echo "$(GREEN)********** Compiled. $(RESET)"

libft:
					@make -C ./libft

clean:
					@$(RM) $(OBJS)
					@make clean -C ./libft
					@echo "$(PURPLE)********* Objects removed. $(RESET)"

fclean: clean
			@$(RM) $(NAME)
			@$(RM) $(LIBFT)
			@echo "$(LIGHTPURPLE)********* Executable removed. $(RESET)"

re: libft fclean all

.PHONY: all clean fclean re libft
