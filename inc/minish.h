/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:22:21 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/02 13:40:16 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISH_H

# define MINISH_H

/*
** Libraries
*/

# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdio.h>
# include <unistd.h>

/*
** Global Variable
*/

int	g_status;

/*
** Define constants
*/

/* Debug */
# define ICI printf("ici\n");
# define LEAKS system("leaks minishell");

/* Colors */
# define RED "\x1B[31m"
# define GREEN "\x1B[32m"
# define YELLOW "\x1B[33m"
# define BLUE "\x1B[34m"
# define MAGENTA "\x1B[35m"
# define CYAN "\x1B[36m"
# define WHITE "\x1B[37m"
# define RESET "\x1B[0m"

/* Managing errors */
# define PIPE_ERR "Error in the creation of a pipe."
# define PWD_ERR "Error in the pwd."
# define FORK_ERR "Error in the creation of a fork."
# define MALLOC_ERR "Error in the memory allocation of a malloc."
# define DUP_ERR "Error in the dup2."
# define CMD_ERR "Wrong input command."
# define DIR_ERR "No such file or directory."
# define NO_EXIT 0
# define EXIT 1

/* Characters */
# define CHILD_PROC 0
# define READ 0
# define WRITE 1
# define S_QUOTE 39
# define D_QUOTE 34
# define PIPE 124

/*
** Structures
*/

typedef struct s_cmd		t_cmd;
typedef struct s_heredoc	t_heredoc;
typedef struct s_mini		t_mini;
typedef struct s_var		t_var;

struct s_var
{
	char	*content;
	t_var	*next;
	t_var	*prev;
};

/* Heredoc structure */
struct s_heredoc
{
	char		*content;
	t_heredoc	*next;
};

/* Command structure */
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

/* Minishell structure */
struct s_mini
{
	int		g_status;
	char	*prompt;
	t_var	*var;
	t_cmd	*cmd;
};

/* Include Libft Header */
# include "../libft/libft.h"

/*
** Functions
*/

/* Main */
char						*get_prompt(t_mini *mini);
t_mini						mini_init(char **env);
int							mini_parser(t_mini *mini, char *str);

/* Utils.c */
int							is_input(char *str);
int							ft_quotes(char *str);
void						mini_exit(t_mini *mini);
char						*mini_getenv(t_mini *mini, char *var);
void						mini_new_line(int sig);
int							start_with_pipe(t_mini *mini, char *str, int i);

/* Parsing & Initialization */
char						**clean_files(t_mini *mini, char **cmds,
								int i, int j, int len);
t_cmd						*cmd_init(t_mini *mini);
int							dol(char *str);
char						**ft_split_cmd(t_mini *mini, char *s, int i, int index, int len);
t_cmd						*get_cmd(t_mini *mini,
								t_cmd *cmd, char *str, int i);
char						*get_exec(t_mini *mini, t_cmd *cmd);
void						get_infile(t_mini *mini, t_cmd *cmd, int i);
int							get_infos_error(t_mini *mini, int i, char *s);
void						get_outfile(t_mini *mini, t_cmd *cmd, int i, int j);
void						get_path(t_mini *mini, t_cmd *cmd, int i);
int							is_var(t_mini *mini, char *var, int j);
void						mini_env(t_mini *mini);
int							mini_heredoc(char *str, int i, int j);
char						*to_empty(char *str);

/* Execution */
void						execute(t_mini *mini);
void						exec_child(t_mini *mini, t_cmd *cmd);

/* Execution UTILS */
int							check_cmd(t_mini *mini, t_cmd *cmd);
int							n_of_cmd(t_cmd *cmd);
void						pipe_and_fork(t_mini *mini, t_cmd *cmd);

/* Builtin */
int							ch_builtin(t_mini *mini, t_cmd *cmd);
void						do_builtin(t_mini *mini, t_cmd *cmd);
void						ft_cd(t_mini *mini, t_cmd *cmd);
void						ft_echo(t_cmd *cmd);
void						ft_env(t_mini *mini);
void						ft_exit(t_mini *mini);
void						ft_export(t_mini *mini, t_cmd *cmd);
void						ft_pwd(t_mini *mini, t_cmd *cmd);
void						ft_unset(t_mini *mini, t_cmd *cmd);
int							par_builtin(t_mini *mini, t_cmd *cmd);


/* Builtin UTILS */
char						*ft_rev_strchr(t_mini *mini, char *str, char c);
int							is_env(t_mini *mini, char *s);
void						remove_quotes(t_cmd *cmd, int index, char *s);

/* Error */
void						ft_error(t_mini *mini, char *type, int is_exit);

/* Free */
void						ft_free_cmd(t_cmd *cmd);
void						ft_free_env(t_var *var);
void						ft_free_full_cmd(char **tab);
void						ft_free_tab(char **tab, int len);

#endif