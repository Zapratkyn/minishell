/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:39:51 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/23 13:41:00 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minish.h"

void	ft_echo(t_cmd *cmd)
{
	int	i;
	int	is_newl;

	i = -1;
	if (!ft_strcmp("-n", cmd->cmd[1]))
		is_newl = 0;
	else
		is_newl = 1;
	while (cmd->cmd[++i])
	{
		if (i != 1 || (i == 1 && is_newl == 1))
			ft_putstr_fd(cmd->cmd[++i], cmd->outfile);
	}
	if (is_newl)
		write (cmd->outfile, "\n", 1);
}
