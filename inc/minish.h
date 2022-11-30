/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:22:21 by gponcele          #+#    #+#             */
/*   Updated: 2022/11/30 17:22:22 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISH_H

# define MINISH_H

/*
** Libraries
*/

# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/ioctl.h>

/*
** Global Variable
*/

int	g_status;

/*
** Define constants
*/

/* Debug */
# define ICI printf("ici\n");

/* Colors */
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN "\x1B[36m"
#define WHITE "\x1B[37m"
#define RESET "\x1B[0m"

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

typedef struct s_mini		t_mini;
typedef struct s_cmd		t_cmd;
typedef struct s_heredoc	t_heredoc;

struct s_heredoc
{
	char		*content;
	t_heredoc	*next;
};

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
	char	*prompt;
	t_var	*var;
	t_cmd	*cmd;
};

int	g_status;

/*
** Functions
*/

// main.c
char						*get_prompt(t_mini *mini);
t_mini  					mini_init(char **env);
int                         mini_parser(t_mini *mini, char *str);
// execute
void						execute(t_mini *mini);
void						exec_child(t_mini *mini, t_cmd *cmd);

// execute utils
int							check_cmd(t_cmd *cmd);
int							n_of_cmd(t_cmd *cmd);
void						pipe_and_fork(t_mini *mini, t_cmd *cmd);

// ft_env.c
void						mini_env(t_mini *mini);
int							is_var(t_mini *mini, char *var, int j);
// void						edit_var(t_mini mini, char *var, char *val);

// int							is_varname(char *str);

// void						mini_export(t_mini mini, char *var, char *val);

// ft_free.c
void						ft_free_cmd(t_cmd *cmd);
void						ft_free_full_cmd(char **tab);
void						ft_free_tab(char **tab);
void						ft_free_env(t_var *var);
void						mini_unlink(char *str);
// builtin_utils.c
char						*ft_rev_strchr(char *str, char c);
int							is_env(t_mini *mini, char *s);
void						remove_quotes(t_cmd *cmd, int index, char *s);
// minishell_utils.c
char						*mini_getenv(t_mini *mini, char *var);
void						mini_exit(t_mini *mini);
int							ft_quotes(char *str);
void						mini_new_line(int sig);
int							is_input(char *str);
int							start_with_pipe(char *str, int i);
// get_cmd.c
t_cmd						*get_cmd(t_mini *mini,
								t_cmd *cmd, char *str, int i);

// get_cmd_utils.c
char						*to_empty(char *str);
int							dol(char *str);
t_cmd						*cmd_init(char *str, int i);
// get_infos.c
char						*get_exec(t_cmd *cmd);
void						get_path(t_mini *mini, t_cmd *cmd, int i);
int							get_infos_error(int i, char *s);
void						get_infile(t_cmd *cmd, int i);
void						get_outfile(t_cmd *cmd, int i, int j);
char						**clean_files(char **cmds, int i, int j, int len);
// ft_split_cmd.c
char						**ft_split_cmd(char *s, int i, int index, int len);

// builtins
int							par_builtin(t_cmd *cmd);
int							ch_builtin(t_cmd *cmd);
void						do_builtin(t_mini *mini, t_cmd *cmd);
void						ft_echo(t_cmd *cmd);
void						ft_env(t_mini *mini);
void						ft_exit(t_mini *mini);
void						ft_cd(t_mini *mini, t_cmd *cmd);
void						ft_pwd(t_cmd *cmd);
void						ft_export(t_mini *mini, t_cmd *cmd);
void						ft_unset(t_mini *mini, t_cmd *cmd);
// heredoc.c
int							mini_heredoc(char *str, int fd);

// error
void						ft_error(char *type, int is_exit);

#endif
