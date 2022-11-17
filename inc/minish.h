/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:22:21 by gponcele          #+#    #+#             */
/*   Updated: 2022/11/15 11:30:09 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISH_H

# define MINISH_H

/*
** Libraries
*/

#include "../libft/libft.h"
#include <stdio.h>
//#include <readline/readline.h>
//#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>

/*
** Define constants
*/


/*
** Structures
*/

typedef struct s_list   t_list;
typedef struct s_prompt t_prompt;

struct s_list
{
    char    *content;
    t_list  *next;
};
struct s_prompt
{
    char    *prompt;
    t_list  *var;
    t_list  *cmd;
};

/*
** Functions
*/

// main.c
void                        get_var(t_prompt *prompt, char *str);
void                        get_env(t_prompt *prompt, char **env);
t_prompt                    *prompt_init(char **env);

#endif