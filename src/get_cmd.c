/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:25:41 by gponcele          #+#    #+#             */
/*   Updated: 2022/11/21 17:40:15 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

int	get_cmd(t_mini *mini, char *str)
{
	if (!str)
		return (0);
	mini->cmd = malloc (sizeof(t_cmd));
	if (!mini->cmd)
		return (0);
	mini->cmd->infile = 0;
	mini->cmd->outfile = 1;
	mini->cmd->full_cmd = ft_split(str, 0, 0);
	return (1);
}