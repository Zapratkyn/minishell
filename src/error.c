/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 12:52:19 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/29 15:28:07 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

void	ft_error(char *type, int is_exit)
{

	ft_putstr_fd(type, STDERR_FILENO);
	write (STDERR_FILENO, "\n", 1);
	if (is_exit == 1)
		exit (0);
}
