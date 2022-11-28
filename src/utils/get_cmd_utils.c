/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:25:41 by gponcele          #+#    #+#             */
/*   Updated: 2022/11/28 16:32:08 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

char	*to_empty(char *str)
{
	free (str);
	return ("");
}

int	dol(char *str)
{
	if (str[0] == '$')
		return (1);
	return (0);
}

t_cmd	*cmd_init(void)
{
	t_cmd	*cmd;

	cmd = malloc (sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->path = NULL;
	cmd->cmds = NULL;
	cmd->infile = 0;
	cmd->outfile = 1;
	cmd->pid = -1;
	cmd->next = NULL;
	return (cmd);
}
