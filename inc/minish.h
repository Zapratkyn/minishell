/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:22:21 by gponcele          #+#    #+#             */
/*   Updated: 2022/11/21 16:12:25 by gponcele         ###   ########.fr       */
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


/*
** Structures
*/

typedef struct s_var    t_var;
typedef struct s_mini   t_mini;
typedef struct s_cmd    t_cmd;

struct s_var
{
    char    *content;
    int     custom;
    t_var   *next;
};

struct s_cmd
{
    char    **full_cmd;
    char    *path;
    int     infile;
    int     outfile;
    t_cmd   *next;
};
struct s_mini
{
    int     g_status;
    char    *prompt;
    t_var   *var;
    t_cmd   *cmd;
    pid_t   pid;
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

#endif