/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:25:41 by gponcele          #+#    #+#             */
/*   Updated: 2022/11/22 11:57:16 by ademurge         ###   ########.fr       */
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
	mini->cmd->full_cmd = ft_split_cmd(str, 0, 0);
	return (1);
}