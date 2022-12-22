/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infos_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:09:16 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/22 13:06:26 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minish.h"

char	*ft_dir(char *str)
{
	write (2, str, ft_strlen(str));
	if (!access(str, F_OK) || ft_strlen(str) == 1)
	{
		write (2, ": is a file or a directory\n", 27);
		g_status = 126;
	}
	else
	{
		write (2, ": No such file or directory\n", 28);
		g_status = 127;
	}
	return (NULL);
}

char	*get_exec(t_mini *mini, t_cmd *cmd, char *exec, int i)
{
	DIR	*dir;

	while (cmd->cmds[i] && (cmd->cmds[i][0] == '<' || cmd->cmds[i][0] == '>'
		|| (i > 0 && cmd->cmds[i - 1][0] == '<' && !cmd->cmds[i - 1][1])
		|| (i > 0 && cmd->cmds[i - 1][0] == '>' && !cmd->cmds[i - 1][1])))
		i++;
	dir = opendir(cmd->cmds[i]);
	if (dir)
	{
		get_infos_error(mini, cmd, 3, cmd->cmds[i]);
		closedir(dir);
		return (NULL);
	}
	if (cmd->cmds[i] && ft_strlen(cmd->cmds[i]) == 1 && cmd->cmds[i][0] == '.')
	{
		write (2, ".: usage: . filename [arguments]\n", 34);
		g_status = 2;
		return (NULL);
	}
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
	while (str[i] == ' ')
		i++;
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
	(void)c;
	if (ft_isdigit(str[1]))
		return (2);
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
