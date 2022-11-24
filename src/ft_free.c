/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:53:43 by gponcele          #+#    #+#             */
/*   Updated: 2022/11/23 16:26:56 by gponcele         ###   ########.fr       */
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