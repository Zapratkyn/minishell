/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:25:41 by gponcele          #+#    #+#             */
/*   Updated: 2022/11/28 14:57:00 by gponcele         ###   ########.fr       */
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
	if (ft_strnstr(str, "$", 10000))
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
	cmd->infile = STDIN_FILENO;
	cmd->outfile = STDOUT_FILENO;
	cmd->pid = -1;
	return (cmd);
}

void	clean_files(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->cmds[i])
	{
		if (cmd->cmds[i][0] == '<' || cmd->cmds[i][0] == '>')
		{
			if (cmd->cmds[i][1])
			{
				free(cmd->cmds[i]);
				cmd->cmds[i] = ft_strdup("");
			}
			else if (!cmd->cmds[i][1] && cmd->cmds[i + 1])
			{
				free (cmd->cmds[i]);
				free (cmd->cmds[i + 1]);
				cmd->cmds[i] = ft_strdup("");
				cmd->cmds[i + 1] = ft_strdup("");
			}
		}
		i++;
	}
}
