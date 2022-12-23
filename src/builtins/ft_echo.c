/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:39:51 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/23 21:41:41 by ademurge         ###   ########.fr       */
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

void	print_space(char **cmds, int i)
{
	if (cmds[i + 1] && cmds[i + 1][0])
		write (STDOUT_FILENO, " ", 1);
	else
	{
		i++;
		while (cmds[i] && !cmds[i][0])
			i++;
		if (cmds[i] && cmds[i][0])
			write (STDOUT_FILENO, " ", 1);
	}
}

void	ft_echo(t_mini *mini, t_cmd *cmd)
{
	int	i;
	int	*newl;

	newl = check_newl(mini, cmd);
	i = newl[0] - 1;
	while (cmd->cmds[++i])
	{
		if (!cmd->cmds[i][0])
			continue ;
		ft_putstr_fd(cmd->cmds[i], STDOUT_FILENO);
		print_space(cmd->cmds, i);
	}
	if (newl[1] == NEW_L)
		write (STDOUT_FILENO, "\n", 1);
	free(newl);
}
