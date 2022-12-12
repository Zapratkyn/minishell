/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:39:51 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/07 14:22:52 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minish.h"

static int	*check_newl(t_mini *mini, t_cmd *cmd)
{
	int	i;
	int	j;
	int	*ret;

	i = 1;
	ret = malloc (sizeof(int) * 2);
	if (!ret)
		ft_error(mini, MALLOC_ERR, EXIT);
	ret[0] = i;
	ret[1] = NEW_L;
	while (cmd->cmds[i] && !ft_strncmp("-n", cmd->cmds[i], 2))
	{
		j = 1;
		while (cmd->cmds[i][++j])
			if (cmd->cmds[i][j] != 'n')
				return (ret);
		ret[0] = ++i;
		ret[1] = NO_NEW_L;
	}
	return (ret);
}

void	ft_echo(t_mini *mini, t_cmd *cmd)
{
	int	i;
	int	*newl;

	newl = check_newl(mini, cmd);
	i = newl[0];
	while (cmd->cmds[i])
	{
		ft_putstr_fd(cmd->cmds[i], STDOUT_FILENO);
		if (cmd->cmds[i][0] && cmd->cmds[i + 1] && cmd->cmds[i + 1][0])
			write (STDOUT_FILENO, " ", 1);
		i++;
	}
	if (newl[1] == NEW_L)
		write (STDOUT_FILENO, "\n", 1);
	free(newl);
}
