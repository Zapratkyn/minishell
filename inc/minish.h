/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:22:21 by gponcele          #+#    #+#             */
/*   Updated: 2022/11/22 12:18:53 by ademurge         ###   ########.fr       */
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

typedef struct s_var	t_var;
typedef struct s_mini	t_mini;
typedef struct s_cmd	t_cmd;

struct s_var
{
	char	*content;
	t_var	*next;
};

struct s_cmd
{
	char	**cmd;
	char	*path;
	int		infile;
	int		outfile;
	t_cmd	*next;
};
struct s_mini
{
	int		env_size;
	char	*prompt;
	t_var	*var;
	t_cmd	*cmd;
	pid_t	pid;
};

/*
** Functions
*/

/*	Main	*/
void						get_var(t_mini *mini, char *str);
void						get_prompt(t_mini *mini);
char						**get_env(t_mini *mini);
t_mini						*mini_init(char **env);

/*	Env	*/
void						mini_env(t_mini *mini);

/*	Free	*/
void						ft_free_env(t_var *var);
void						ft_free_cmd(t_cmd *cmd);
void						ft_free_full_cmd(char **tab);

/*	Utils	*/
char						*mini_getenv(t_mini *mini, char *var);
void						mini_exit(int sig);

/*	Get_Cmd	*/
int							get_cmd(t_mini *mini, char *str);
char						**ft_split_cmd(char *s, int i, int index);

/*	Execute */
void						execute(t_mini *mini);
#endif