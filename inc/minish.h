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

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>

/*
** Define constants
*/


/*
** Structures
*/
struct s_main
{
    char    *prompt;
    char    **env;
    t_list  *cmd;
}t_main;

/*
** Functions
*/


#endif