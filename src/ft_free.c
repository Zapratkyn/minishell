/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:53:43 by gponcele          #+#    #+#             */
/*   Updated: 2022/11/24 10:15:58 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

void    ft_free_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->cmds[i])
	{
		free (cmd->cmds[i]);
		i++;
	}
	free (cmd->cmds);
	if (cmd->next)
        ft_free_cmd(cmd->next);
    free (cmd);
}

void	ft_free_full_cmd(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free (tab[i]);
		i++;
	}
	free (tab);
}

void	ft_free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
		free (paths[i++]);
	free (paths);
}