/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:53:43 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/13 15:26:27 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

void	ft_free_all(t_mini *mini)
{
	if (mini->prompt)
		free(mini->prompt);
	if (mini->var)
		ft_lstclear(mini->var);
	ft_free_tab(mini->paths, ft_tablen(mini->paths));
	if (mini->cmd && mini->cmd->cmds)
		mini->cmd = ft_free_cmd(mini->cmd);
	if (mini->temptab)
		ft_free_tab(mini->temptab, ft_tablen(mini->temptab));
	if (mini->tempstr)
		free (mini->tempstr);
	if (mini->tempstr2)
		free (mini->tempstr2);
	rl_clear_history();
}

t_cmd	*ft_free_cmd(t_cmd *cmd)
{
	if (cmd->cmds)
		ft_free_tab(cmd->cmds, ft_tablen(cmd->cmds));
	if (cmd->path)
		free (cmd->path);
	if (cmd->next)
		ft_free_cmd(cmd->next);
	free (cmd);
	return (NULL);
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
	char	*nb;
	char	*file;

	i = 1;
	file = NULL;
	while (1)
	{
		nb = ft_itoa(mini, i);
		file = ft_strdup(mini, str);
		file = ft_strjoin(mini, file, nb);
		free (nb);
		if (access(file, F_OK))
			break ;
		unlink(file);
		free (file);
		i++;
	}
	free (file);
}
