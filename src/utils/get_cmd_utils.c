/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:25:41 by gponcele          #+#    #+#             */
/*   Updated: 2022/11/29 11:51:09 by gponcele         ###   ########.fr       */
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

char	**clean_files(char **cmds, int i, int j, int len)
{
	char	**result;

	while (cmds[++i])
	{
		if (cmds[i] && cmds[i][0] != '<' && cmds[i][0] != '>'
			&& !(i > 0 && cmds[i - 1][0] != '<' && !cmds[i - 1][1])
			&& !(i > 0 && cmds[i - 1][0] != '>' && !cmds[i - 1][1]))
			len++;
	}
	result = malloc (sizeof(char *) *  len + 1);
	if (!result)
		return (NULL);
	i = -1;
	while (cmds[++i])
	{
		if (cmds[i] && cmds[i][0] != '<' && cmds[i][0] != '>'
			&& !(i > 0 && cmds[i - 1][0] != '<' && !cmds[i - 1][1])
			&& !(i > 0 && cmds[i - 1][0] != '>' && !cmds[i - 1][1]))
			result[j++] = ft_strdup(cmds[i]);
	}
	result[j] = NULL;
	free (cmds);
	return (result);
}
