/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:22:21 by gponcele          #+#    #+#             */
/*   Updated: 2022/11/23 12:55:21 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISH_H

# define MINISH_H

/*
** Libraries
*/

#include "../libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <signal.h>

/*
** Define constants
*/

/* Managing erros */
# define PIPE_ERR "Error in the creation of a pipe."
# define FORK_ERR "Error in the creation of a fork."
# define MALLOC_ERR "Error in the memory allocation of a malloc."
# define DUP_ERR "Error in the dup2."
# define CMD_ERR "Wrong input command."

/* Characters */
# define CHILD 0
# define READ 0
# define WRITE 1
# define S_QUOTE 39
# define PIPE 124

/* Builtin */
# define ECHO 1
# define CD 2
# define PWD 3
# define EXPORT 4
# define UNSET 5
# define ENV 6
# define EXIT 7

/*
** Structures
*/

typedef struct s_var	t_var;
typedef struct s_mini	t_mini;
typedef struct s_cmd	t_cmd;

struct s_var
{
    char    *content;
    int     custom;
    t_var   *next;
};

struct s_cmd
{
	char	**cmd;
	char	*path;
	int		infile;
	int		outfile;
	pid_t	pid;
	int		fd[2];
	t_cmd	*next;
};

struct s_mini
{
	char	**env;
	int		g_status;
	char	*prompt;
	t_var	*var;
	t_cmd	*cmd;
	pid_t	pid;
};

/*
** Functions
*/

// main.c
void                        get_var(t_mini *mini, char *str);
void                        get_prompt(t_mini *mini);
char                        **get_env(t_mini *mini);
t_mini                      *mini_init(char **env);
// ft_env.c
void                        mini_env(t_mini *mini, int i);
int	                        is_var(t_mini *mini, char *var);
void	                    edit_var(t_mini *mini, char *var, char *val);
int	                        is_varname(char *str);
void	                    mini_export(t_mini *mini, char *var, char *val);
// ft_free.c
void                        ft_free_env(t_var *var);
void                        ft_free_cmd(t_cmd *cmd);
void						ft_free_full_cmd(char **tab);
// minishell_utils.c
char                        *mini_getenv(t_mini *mini, char *var);
void    					mini_exit(int sig);
char                        *ft_varname(char *str);
void                        mini_add_history(t_mini *mini, t_cmd *cmd, char *str);
// get_cmd.c
void						get_cmd(t_mini *mini, t_cmd *cmd, char *str, int i);
// ft_split.c
int	                        ft_quotes(char *str);
char						**ft_split_cmd(char *s, int i, int index);
// builtin.c
int							is_builtin(t_cmd *cmd);
void						do_builtin(t_cmd *cmd, int builtin);
// error
void						ft_error(char *type);
#endif