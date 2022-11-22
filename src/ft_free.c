/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:53:43 by gponcele          #+#    #+#             */
/*   Updated: 2022/11/21 16:19:00 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

void    ft_free_env(t_var *var)
{
    if (var->next)
        ft_free_env(var->next);
    free (var);
}

void    ft_free_cmd(t_cmd *cmd)
{
	// int	i;

	// i = 0;
    if (cmd->next)
        ft_free_cmd(cmd->next);
	// while (cmd->full_cmd[i])
	// 	free (cmd->full_cmd[i++]);
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