/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infos_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:09:16 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/12 16:38:54 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

char	*get_exec(t_mini *mini, t_cmd *cmd)
{
	char	*exec;
	int		i;

	i = 0;
	exec = NULL;
	while (cmd->cmds[i] && (cmd->cmds[i][0] == '<' || cmd->cmds[i][0] == '>'
		|| (i > 0 && cmd->cmds[i - 1][0] == '<' && !cmd->cmds[i - 1][1])
		|| (i > 0 && cmd->cmds[i - 1][0] == '>' && !cmd->cmds[i - 1][1])))
		i++;
	if (cmd->cmds[i])
	{
		exec = ft_strdup(mini, cmd->cmds[i]);
		exec = manage_string(mini, exec, 1);
	}
	return (exec);
}

int	quotes(char *str, char c, int i)
{
	c = str[i++];
	while (str[i] != c)
		i++;
	return (i + 1);
}

// char	*dollar(char *str, int i, int j)
// {
	
// }