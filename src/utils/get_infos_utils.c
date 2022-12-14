/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infos_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:09:16 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/14 11:31:55 by gponcele         ###   ########.fr       */
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

void	get_input(t_mini *mini, char *str, char c)
{
	int	i;

	i = 0;
	mini->tempstr = ft_strdup(mini, "");
	while (str[i] && str[i] != PIPE)
	{
		if (str[i] == '"' || str[i] == S_QUOTE)
		{
			mini->tempstr = ft_strjoin2(mini, mini->tempstr, str[i]);
			c = str[i++];
			while (str[i] != c)
				mini->tempstr = ft_strjoin2(mini, mini->tempstr, str[i++]);
			mini->tempstr = ft_strjoin2(mini, mini->tempstr, str[i++]);
		}
		else
			mini->tempstr = ft_strjoin2(mini, mini->tempstr, str[i++]);
	}
}

int	dollar(char *str, int i, char c)
{
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'
				|| str[i] == '?'))
	{
		if (str[i] == '"' || str[i] == S_QUOTE)
		{
			c = str[i++];
			while (str[i] != c)
				i++;
			i++;
		}
		else
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'
				|| str[i] == '?'))
				i++;
	}
	return (i);
}
