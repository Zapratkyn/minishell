/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:22:21 by gponcele          #+#    #+#             */
/*   Updated: 2022/11/24 13:39:36 by ademurge         ###   ########.fr       */
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
#include <fcntl.h>

/*
** Define constants
*/

/* Debug */
# define ICI printf("ici\n");

/* Managing errors */
# define PIPE_ERR "Error in the creation of a pipe."
# define PWD_ERR "Error in the pwd."
# define FORK_ERR "Error in the creation of a fork."
# define MALLOC_ERR "Error in the memory allocation of a malloc."
# define DUP_ERR "Error in the dup2."
# define CMD_ERR "Wrong input command."
# define DIR_ERR "No such file or directory."

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

typedef struct s_cmd	t_cmd;
typedef struct s_mini	t_mini;


struct s_cmd
{
	char	**cmds;
	char	*path;
	int		infile;
	int		outfile;
	pid_t	pid;
	int		fd[2];
	t_cmd	*next;
};

struct s_mini
{
	int		g_status;
	char	**env;
	t_list	*l_env;
	t_cmd	*cmd;
	pid_t	pid;
};

/*
** Functions
*/

// main.c
void						get_prompt(t_mini *mini);
void						mini_init(t_mini *mini, char **env);

// execute
void						execute(t_mini *mini);

// ft_env.c
void                        mini_env(t_mini *mini);
int	                        is_var(t_mini *mini, char *var, int j);
// void	                    edit_var(t_mini mini, char *var, char *val);

// int	                        is_varname(char *str);

// void	                    mini_export(t_mini mini, char *var, char *val);

// ft_free.c
void                        ft_free_cmd(t_cmd *cmd);
void						ft_free_full_cmd(char **tab);
void	                    ft_free_paths(char **paths);
// minishell_utils.c
char                        *mini_getenv(t_mini *mini, char *var);
void    					mini_exit(int sig);
int	                        ft_quotes(char *str);
char                        *ft_varname(char *str);
void                        mini_parser(t_mini *mini, char *str);
// get_cmd.c
t_cmd						*get_cmd(t_mini *mini, t_cmd *cmd, char *str, int i);
// get_cmd_utils.c
char	                    *to_empty(char *str);
int                         dol(char *str);
// get_infos.c
char                        *get_exec(t_cmd *cmd);
void                        get_path(t_mini *mini, t_cmd *cmd, int i);
void                        get_infile(t_cmd *cmd, int i);
void                        get_outfile(t_cmd *cmd, int i);
// ft_split_cmd.c
char						**ft_split_cmd(char *s, int i, int index);

// builtins
int							is_builtin(t_cmd *cmd);
void						do_builtin(t_mini *mini, t_cmd *cmd);
void						ft_echo(t_cmd *cmd);
void						ft_env(t_mini *mini, t_cmd *cmd);
void						ft_cd(t_mini *mini, t_cmd *cmd);
void						ft_pwd(t_cmd *cmd);
void						update_pwd(t_mini *mini, char *type);

// error
void						ft_error(char *type);
#endif