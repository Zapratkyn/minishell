/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infos_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:09:16 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/13 12:30:33 by gponcele         ###   ########.fr       */
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

char	*get_input(t_mini *mini, char *str, char *result, char c)
{
	int	i;

	i = 0;
	result = ft_strdup(mini, "");
	while (str[i] && str[i] != PIPE)
	{
		if (str[i] == '"' || str[i] == S_QUOTE)
		{
			result = ft_strjoin2(mini, result, str[i]);
			c = str[i++];
			while (str[i] != c)
				result = ft_strjoin2(mini, result, str[i++]);
			result = ft_strjoin2(mini, result, str[i++]);
		}
		else
			result = ft_strjoin2(mini, result, str[i++]);
	}
	return (result);
}

int	dollar(char *str, int i, char c)
{
	while (str[i])
	{
		if (str[i] == '"' || str[i] == S_QUOTE)
		{
			c = str[i++];
			while (str[i] != c)
				i++;
			i++;
		}
		else
			while (ft_isalnum(str[i]) || str[i] == '_')
				i++;
	}
	return (i);
}
