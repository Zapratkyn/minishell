/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:25:41 by gponcele          #+#    #+#             */
/*   Updated: 2022/11/22 14:46:20 by ademurge         ###   ########.fr       */
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
	mini->cmd->infile = STDIN_FILENO;
	mini->cmd->outfile = STDOUT_FILENO;
	mini->cmd->cmd = ft_split_cmd(str, 0, 0);
	return (1);
}