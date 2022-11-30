/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:39:51 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/24 10:18:25 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minish.h"

void	ft_echo(t_cmd *cmd)
{
	int	i;
	int	is_newl;

	if (cmd->cmds[1] && !ft_strcmp("-n", cmd->cmds[1]))
		is_newl = 0;
	else
		is_newl = 1;
	i = 0;
	while (cmd->cmds[++i])
		if (i != 1 || (i == 1 && is_newl == 1))
			ft_putstr_fd(cmd->cmds[i], cmd->outfile);
	if (is_newl)
		write (cmd->outfile, "\n", 1);
}
