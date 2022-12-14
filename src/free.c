/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:53:43 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/14 12:10:40 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

void	ft_free_all(t_mini *mini)
{
	if (mini->prompt)
		free(mini->prompt);
	if (mini->var)
		ft_lstclear(mini->var);
	mini->paths = ft_free_tab(mini->paths, ft_tablen(mini->paths));
	if (mini->cmd && mini->cmd->cmds)
		mini->cmd = ft_free_cmd(mini->cmd);
	if (mini->temptab)
		mini->temptab = ft_free_tab(mini->temptab, ft_tablen(mini->temptab));
	if (mini->tempstr)
		mini->tempstr = ft_free(mini->tempstr);
	if (mini->tempstr2)
		mini->tempstr2 = ft_free(mini->tempstr2);
	if (mini->tempstr3)
		mini->tempstr3 = ft_free(mini->tempstr3);
	if (mini->tempstr4)
		mini->tempstr4 = ft_free(mini->tempstr4);
	if (mini->tempstr5)
		mini->tempstr5 = ft_free(mini->tempstr5);
	rl_clear_history();
}

t_cmd	*ft_free_cmd(t_cmd *cmd)
{
	if (cmd->cmds)
		cmd->cmds = ft_free_tab(cmd->cmds, ft_tablen(cmd->cmds));
	if (cmd->path)
		free (cmd->path);
	if (cmd->next)
		ft_free_cmd(cmd->next);
	free (cmd);
	return (NULL);
}

char	**ft_free_tab(char **tab, int len)
{
	int	i;

	i = -1;
	while (++i < len)
		if (tab && tab[i])
			tab[i] = ft_free(tab[i]);
	free (tab);
	return (NULL);
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

char	*ft_free(char *str)
{
	if (str)
		free (str);
	return (NULL);
}
