/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:25:41 by gponcele          #+#    #+#             */
/*   Updated: 2022/11/23 18:37:01 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

char	*delete_quotes(char *str, char c)
{
	char	*result;
	int		i;
	int		j;

	i = 1;
	j = 0;
	result = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	while (str[i] != c)
	{
		result[j] = str[i];
		i++;
		j++;
	}
	free (str);
	return (result);
}

char	*ft_var(t_mini *mini, char *str)
{
	int		i;
	int		j;
	int		len;
	char	*result;

	i = 0;
	j = 0;
	len = 0;
	if (!is_var(mini, str, 0))
		return (NULL);
	len = is_var(mini, str, 1);
	result = malloc (sizeof(char) * len + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (i < len)
		result[j++] = str[i++];
	result[i] = '\0';
	return (result);
}

char	*delete_double_quotes(t_mini *mini, char *str, int i)
{
	char	*result;
	char	*var;
	
	result = calloc(1, 1);
	if (!result)
		return (NULL);
	while (str[++i] != '"')
	{
		if (str[i] == '$')
		{
			var = ft_var(mini, &str[i + 1]);
			if (var)
			{
				result = ft_strjoin(result, mini_getenv(mini, var));
				i += (ft_strlen(var));
				free (var);
			}
			else
				i += is_var(mini, &str[i + 1], 1);
		}
		else
			result = ft_strjoin2(result, str[i]);
	}
	
	return (result);
}

char	*to_var(t_mini *mini, char *str)
{
	char	*result;

	result = ft_strdup(mini_getenv(mini, &str[1]));
	if (!result)
		return (NULL);
	free (str);
	return (result);
}

t_cmd	*get_cmd(t_mini *mini, t_cmd *cmd, char *str, int i)
{
	cmd = malloc (sizeof(t_cmd));
	if (cmd && (str[1] || (str[0] != S_QUOTE && str[0] != '"')))
	{
		cmd->cmds = ft_split_cmd(str, 0, 0);
		while (cmd->cmds[i])
		{
			if (!ft_quotes(cmd->cmds[i]))
				free (cmd->cmds[i]);
			else if (cmd->cmds[i][0] == S_QUOTE)
				cmd->cmds[i] = delete_quotes(cmd->cmds[i], S_QUOTE);
			else if (cmd->cmds[i][0] == '"')
				cmd->cmds[i] = delete_double_quotes(mini, cmd->cmds[i], 0);
			else if (dol(cmd->cmds[i]) && !is_var(mini, &cmd->cmds[i][1], 0))
				cmd->cmds[i] = to_empty(cmd->cmds[i]);
			else if (dol(cmd->cmds[i]) && is_var(mini, &cmd->cmds[i][1], 0))
				cmd->cmds[i] = to_var(mini, cmd->cmds[i]);
			i++;
		}
		get_path(mini, cmd, 0);
		if (cmd->cmds && ft_strchr(str, PIPE))
			cmd->next = get_cmd(mini, cmd->next, &ft_strchr(str, PIPE)[1], 0);
	}
	return (cmd);
}
