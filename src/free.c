/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:53:43 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/07 12:17:40 by gponcele         ###   ########.fr       */
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
	char	*nb;
	char	*file;

	i = 1;
	file = NULL;
	while (1)
	{
		nb = ft_itoa(i);
		file = ft_strdup(str);
		file = ft_strjoin(file, nb);
		free (nb);
		if (access(file, F_OK))
			break ;
		unlink(file);
		free (file);
		i++;
	}
	free (file);
}
