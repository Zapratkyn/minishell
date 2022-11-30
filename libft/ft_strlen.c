/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
<<<<<<< HEAD:inc/minish.h
/*   minish.h                                           :+:      :+:    :+:   */
=======
/*   ft_strlen.c                                        :+:      :+:    :+:   */
>>>>>>> levraigponcele:libft/ft_strlen.c
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:inc/minish.h
/*   Created: 2022/11/15 11:22:21 by gponcele          #+#    #+#             */
/*   Updated: 2022/11/15 17:41:08 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISH_H

# define MINISH_H

/*
** Libraries
*/
=======
/*   Created: 2022/07/04 18:07:27 by gponcele          #+#    #+#             */
/*   Updated: 2022/07/11 14:13:28 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
>>>>>>> levraigponcele:libft/ft_strlen.c

size_t	ft_strlen(const char *s)
{
	size_t	i;

<<<<<<< HEAD:inc/minish.h
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
=======
	i = 0;
	while (s[i])
		i++;
	return (i);
}
>>>>>>> levraigponcele:libft/ft_strlen.c
