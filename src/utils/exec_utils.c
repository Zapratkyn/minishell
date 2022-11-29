/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:13:44 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/29 11:52:52 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minish.h"

int	check_cmd(t_cmd *cmd)
{
	if (cmd->infile == -1 || cmd->outfile == -1)
		return (0);
	if (!is_builtin(cmd) && !cmd->path)
		return (0);
	return (1);
}

int	n_of_cmd(t_cmd *cmd)
{
	int		n;
	t_cmd	*tmp;

	n = 0;
	tmp = cmd;
	while (tmp)
	{
		n++;
		tmp = tmp->next;
	}
	return (n);
}
