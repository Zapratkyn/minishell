/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:53:43 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/06 18:36:41 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

t_cmd	*ft_free_cmd(t_cmd *cmd)
{
	ft_free_tab(cmd->cmds);
	free (cmd->path);
	if (cmd->next)
		ft_free_cmd(cmd->next);
	free (cmd);
	return (NULL);
}

// void	ft_free_full_cmd(char **tab)
// {
// 	int	i;

// 	i = 0;
// 	while (tab[i])
// 	{
// 		free (tab[i]);
// 		i++;
// 	}
// 	free (tab);
// }

void	ft_free_tab(char **tab)
{
	int	i;
	int	len;

	len = ft_tablen(tab);
	i = 0;
	while (tab && i < len)
	{
		if (tab[i])
			free (tab[i]);
		i++;
	}
	if (tab)
		free (tab);
}

void	ft_free_env(t_var *var)
{
	if (var->next)
		ft_free_env(var->next);
	free(var);
}

void	mini_unlink(char *str)
{
	int		i;
	char	*file;

	i = 1;
	file = NULL;
	while (1)
	{
		file = ft_strdup(str);
		file = ft_strjoin(file, ft_itoa(i));
		if (access(file, F_OK))
			break ;
		unlink(file);
		free (file);
		i++;
	}
	free (file);
}
