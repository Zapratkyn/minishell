/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 12:52:19 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/25 16:47:16 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

void	ft_error(char *type, int is_exit)
{
	if (is_exit == 0)
	{
		ft_putstr_fd(type, STDERR_FILENO);
		write (STDERR_FILENO, "\n", 1);
	}
	if (is_exit == 1)
		exit (0);
}
