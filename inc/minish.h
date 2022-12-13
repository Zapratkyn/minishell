/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:22:21 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/13 18:41:53 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISH_H

# define MINISH_H

/*
** Libraries
*/

# include <fcntl.h>
# include <limits.h>
# include <sys/ioctl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/ioctl.h>
// # include <sys/types.h>
# include <sys/wait.h>
// # include <stddef.h>
# include <stdlib.h>
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
# define ARG_ERR "minishell: exit: too many arguments"
# define CMD_ERR "minishell : wrong input command"
# define DIR_ERR "minishell: no such file or directory"
# define DUP_ERR "minishell : error in the dup2."
# define EXIT 1
# define EXPORT_ERR "minishell: export: not a valid identifier"
# define FORK_ERR "minishell : error in the creation of a fork."
# define MALLOC_ERR "minishell : error in the memory allocation of a malloc."
# define NUM_ERR "minishell: exit: numeric argument required"
# define NO_EXIT 0
# define PIPE_ERR "minishell : error in the creation of a pipe."
# define PWD_ERR "minishell : error in the pwd."
# define UNSET_NAME_ERR "minishell: unset: invalid parameter name"
# define UNSET_ID_ERR "minishell: unset: not a valid identifier"

/* Characters */
# define CHILD_PROC 0
# define READ 0
# define WRITE 1
# define S_QUOTE 39
# define D_QUOTE 34
# define PIPE 124
# define NO_NEW_L 0
# define NEW_L 1

/*
** Structures
*/

/* Var structure */
typedef struct s_var
{
	char			*content;
	struct s_var	*next;
	struct s_var	*prev;
}	t_var;

/* Command structure */
typedef struct s_cmd
{
	char			**cmds;
	char			*path;
	int				cmds_nb;
	int				infile;
	int				outfile;
	pid_t			pid;
	int				fd[2];
	struct s_cmd	*next;
}	t_cmd;

/* Minishell structure */
typedef struct s_mini
{
	char	*prompt;
	char	**paths;
	char	*tempstr;
	char	*tempstr2;
	char	*tempstr3;
	char	*tempstr4;
	char	*tempstr5;
	char	**temptab;
	t_var	*var;
	t_cmd	*cmd;
}	t_mini;

/*
** Functions
*/

/* Main */
char					*get_prompt(t_mini *mini, char *prompt);
void					mini_init(t_mini *mini, char **env);
int						mini_parser(t_mini *mini, char *str);

/* Utils.c */
int						is_input(t_mini *mini, char *str);
char					*fill_parts(t_mini *mini, char **parts,
							char *str, int i);
int						ft_quotes(char *str, int i, int quotes,
							int double_quotes);
char					*manage_string(t_mini *mini, char *str, int i);
void					mini_exit(t_mini *mini);
char					*mini_getenv(t_mini *mini, char *var);
int						mini_get_status(t_mini *mini, char *var, int j);
void					mini_new_line(int sig);
void					split_string(t_mini *mini, char *s, int i, int index);
int						ft_pipes(char *str, int i);
int						ft_pipes2(char *str, int i);
char					**transform_parts(t_mini *mini, char **parts,
							int i, int len);
int						end_of_heredoc(char *input, char *eof);
char					*get_vars(t_mini *mini, char *str, int i);
int						eof_to_fd(t_mini *mini, char *str, int fd, char *file);
char					*get_exec(t_mini *mini, t_cmd *cmd);

/* Parsing & Initialization */
char					**clean_files(t_mini *mini, char **cmds,
							int i, int j);
t_cmd					*cmd_init(t_mini *mini, char *str);
void					delete_double_quotes(t_mini *mini, char *str, int i);
void					delete_quotes(t_mini *mini, char *str, int i, int j);
int						dollar(char *str, int i, char c);
char					**ft_split_cmd(t_mini *mini, char *s, int i,
							int index);
char					*ft_var(t_mini *mini, char *str, char *result);
t_cmd					*get_cmd(t_mini *mini,
							t_cmd *cmd, char *str, int i);
char					*get_exec(t_mini *mini, t_cmd *cmd);
void					get_infile(t_mini *mini, t_cmd *cmd, int i);
void					get_outfile(t_mini *mini, t_cmd *cmd, int i, int j);
void					get_path(t_mini *mini, t_cmd *cmd, int i);
char					*get_vars(t_mini *mini, char *str, int i);
int						is_var(t_mini *mini, char *var);
void					mini_env(t_mini *mini);
int						mini_heredoc(t_mini *mini, t_cmd *cmd, int fd, int i);
char					*to_empty(char *str);
int						quotes(char *str, char c, int i);
void					get_input(t_mini *mini, char *str, char c);
void					put_shell(void);

/* Execution */
void					execute(t_mini *mini);
void					exec_child(t_mini *mini, t_cmd *cmd);
int						to_exec(t_mini *mini);

/* Execution UTILS */
int						check_cmd(t_mini *mini, t_cmd *cmd);
int						n_of_cmd(t_cmd *cmd);
void					pipe_and_fork(t_mini *mini, t_cmd *cmd);

/* Builtin */
int						check_builtin(t_mini *mini, t_cmd *cmd);
int						ch_builtin(t_cmd *cmd);
void					do_builtin(t_mini *mini, t_cmd *cmd);
void					ft_cd(t_mini *mini, t_cmd *cmd);
void					ft_echo(t_mini *mini, t_cmd *cmd);
void					ft_env(t_mini *mini);
void					ft_exit(t_mini *mini, t_cmd *cmd);
void					ft_export(t_mini *mini, t_cmd *cmd);
void					ft_pwd(t_mini *mini);
void					ft_unset(t_mini *mini, t_cmd *cmd, int i, char *s);
int						par_builtin(t_cmd *cmd);

/* Builtin UTILS */
int						check_option(t_mini *mini, t_cmd *cmd, char *s);
char					*ft_rev_strchr(t_mini *mini, char *str, char c);
int						is_env(t_mini *mini, char *s);
void					modif_var(t_mini *mini, char *name_var, char *s);

/* Error */
void					ft_error(t_mini *mini, char *type, int is_exit);
int						unclosed_quotes(void);
int						get_infos_error(t_mini *mini,
							t_cmd *cmd, int i, char *s);
int						spike_error(t_mini *mini, char *str);
int						dir(t_mini *mini, char *str, int i, char c);

/* Free */
void					ft_free_all(t_mini *mini);
t_cmd					*ft_free_cmd(t_cmd *cmd);
void					ft_free_full_cmd(char **tab);
char					**ft_free_tab(char **tab, int len);
void					mini_unlink(t_mini *mini, char *str);
char					*ft_free(char *str);

/* Linked List */
int						ft_lst_index(t_var **l_var, t_var *var);
char					**ft_lst_to_str(t_mini *mini, t_var *var);
void					ft_lstadd_back(t_var **var, t_var *new);
void					ft_lstclear(t_var *var);
void					ft_lstdelone(t_var **l_var, int i);
t_var					*ft_lstdup(t_mini *mini, t_var *var);
t_var					*ft_lstget(t_var *var, int index);
t_var					*ft_lstlast(t_var *var);
t_var					*ft_lstnew(t_mini *mini, char *content);
int						ft_lstsize(t_var *var);
t_var					*ft_sortlst(t_var *var);

/* Libft */
int						ft_atoi(const char *str);
char					*ft_calloc(t_mini *mini, int count, int size);
void					ft_error(t_mini *mini, char *type, int is_exit);
int						ft_find_index(char *s, char c);
char					*ft_insert(t_mini *mini, char *s1, char c, char *s2);
int						ft_isalnum(int c);
char					*ft_itoa(t_mini *mini, int n);
void					ft_n_putstr(char *s, int n);
void					ft_putendl_fd(char *s, int fd);
void					ft_putstr_fd(char *s, int fd);
void					ft_put_tab(char **tab);
char					**ft_split(t_mini *mini, char const *s, char c);
void					ft_split_paths(t_mini *mini, char const *s, char c);
char					*ft_strchr(const char *s, int c);
char					*ft_strchr_minishell(const char *s, int c, char k);
int						ft_strcmp(char *s1, char *s2);
char					*ft_strdup(t_mini *mini, char *str);
char					*ft_strdup2(t_mini *mini, char *str);
char					*ft_strjoin(t_mini *mini, char const *s1,
							char const *s2);
char					*ft_strjoin2(t_mini *mini, char *str, char c);
char					*ft_strjoin3(t_mini *mini,
							char const *s1, char const *s2);
size_t					ft_strlcpy(char *dest, const char *src, size_t size);
size_t					ft_strlen(const char *s);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
char					*ft_strnstr(const char *haystack, const char *needle,
							size_t len);
char					*ft_strnstr2(const char *haystack, const char *needle,
							size_t len);
char					*ft_substr(t_mini *mini, char const *s,
							unsigned int start, size_t len);
int						ft_tablen(char **tab);

#endif
