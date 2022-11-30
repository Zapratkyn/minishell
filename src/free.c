/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:53:43 by gponcele          #+#    #+#             */
/*   Updated: 2022/11/30 12:06:54 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

void	ft_free_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->next)
		ft_free_cmd(cmd->next);
	while (cmd->cmds[i])
	{
		free (cmd->cmds[i]);
		i++;
	}
	free (cmd->cmds);
	if (cmd->path)
		free (cmd->path);
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

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free (tab[i++]);
	free (tab);
}

void	ft_free_env(t_var *var)
{
	if (var->next)
		ft_free_env(var->next);
	free(var);
}
