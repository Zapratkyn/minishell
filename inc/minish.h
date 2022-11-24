/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:22:21 by gponcele          #+#    #+#             */
/*   Updated: 2022/11/23 16:18:49 by gponcele         ###   ########.fr       */
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

# define S_QUOTE 39
# define PIPE 124
/*
** Structures
*/

typedef struct s_var    t_var;
typedef struct s_mini   t_mini;
typedef struct s_cmd    t_cmd;

struct s_var
{
    char    *content;
    t_var   *next;
};

struct s_cmd
{
    char    **cmds;
    char    *path;
    int     infile;
    int     outfile;
    pid_t   pid;
    t_cmd   *next;
};
struct s_mini
{
    int     g_status;
    char	**env;
    char    *prompt;
    t_var   *var;
    t_cmd   *cmd;
    pid_t   pid;
};

/*
** Functions
*/

// main.c
char                        *get_prompt(t_mini *mini);
t_mini  					mini_init(char **env);
int                         mini_parser(t_mini *mini, char *str);
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
void	                    ft_free_env(t_var *var);
// minishell_utils.c
char                        *mini_getenv(t_mini *mini, char *var);
void                        mini_exit(t_mini *mini);
int	                        ft_quotes(char *str);
char                        *ft_varname(char *str);
int	                        is_input(char *str);
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

#endif