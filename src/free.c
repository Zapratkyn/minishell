/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:53:43 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/06 15:45:32 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

void	ft_free_all(t_mini *mini)
{
	if (mini->prompt)
		free(mini->prompt);
	if (mini->var)
	{
		ft_lstclear(&mini->var);
		free(mini->var);
	}
	if (mini->cmd)
		ft_free_cmd(mini->cmd);
}

void	ft_free_cmd(t_cmd *cmd)
{
	int		i;
	t_cmd	*tmp;
	t_cmd	**clear;

	clear = NULL;
	tmp = cmd;
	while (tmp)
	{
		i = -1;
		while (tmp->cmds && tmp->cmds[++i])
			free (tmp->cmds[i]);
		if (tmp->cmds)
			free(tmp->cmds);
		if (tmp->path)
			free (tmp->path);
		tmp = tmp->next;
	}
	clear = &cmd;
	while (clear && *clear)
	{
		tmp = (*clear)->next;
		free((*clear));
		*clear = tmp;
	}
}

void	ft_free_tab(char **tab, int len)
{
	int	i;

	i = -1;
	while (++i < len)
		if (tab && tab[i])
			free (tab[i]);
	if (tab)
		free (tab);
}

void	mini_unlink(t_mini *mini, char *str)
{
	int		i;
	char	*file;

	i = 1;
	file = NULL;
	while (1)
	{
		if (file)
			free (file);
		file = ft_strdup(mini, str);
		file = ft_strjoin(mini, file, ft_itoa(mini, i));
		if (access(file, F_OK))
			break ;
		unlink(file);
		i++;
	}
	free (file);
}
