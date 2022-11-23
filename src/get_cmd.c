/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:25:41 by gponcele          #+#    #+#             */
/*   Updated: 2022/11/23 17:29:59 by ademurge         ###   ########.fr       */
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
	while (ft_isalnum(str[i]) || str[i] != '_')
	{
		len++;
		i++;
	}
	result = malloc (sizeof(char) * len + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (str[i] != '"' && str[i] != ' ')
		result[j++] = str[i++];
	result[i] = '\0';
	return (result);
}

char	*delete_double_quotes(t_mini *mini, char *str, int i)
{
	char	*result;
	char	*var;

	result = malloc(sizeof(char) * 1);
	if (!result)
		return (NULL);
	while (str[i + 1] != '"')
	{
		if (str[i + 1] == '$')
		{
			var = ft_var(mini, &str[i + 2]);
			if (var)
			{
				result = ft_strjoin(result, mini_getenv(mini, var));
				i += (ft_strlen(var) + 1);
				free (var);
			}
			else
				i += is_var(mini, &str[i + 2], 1);
		}
		else
			result = ft_strjoin2(result, str[++i]);
	}
	free (str);
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

char	*to_empty(char *str)
{
	free (str);
	return (" ");
}

t_cmd	*get_cmd(t_mini *mini, t_cmd *cmd, char *str, int i)
{
	cmd = malloc (sizeof(t_cmd));
	cmd->next = NULL;
	if (cmd)
	{
		cmd->cmd = ft_split_cmd(str, 0, 0);
		while (cmd->cmd[i])
		{
			if (cmd->cmd[i][0] == S_QUOTE)
				cmd->cmd[i] = delete_quotes(cmd->cmd[i], S_QUOTE);
			else if (cmd->cmd[i][0] == '"')
				cmd->cmd[i] = delete_double_quotes(mini, cmd->cmd[i], 0);
			else if (cmd->cmd[i][0] == '$' && !is_var(mini, &cmd->cmd[i][1], 0))
				cmd->cmd[i] = to_empty(cmd->cmd[i]);
			else if (cmd->cmd[i][0] == '$' && is_var(mini, &cmd->cmd[i][1], 0))
				cmd->cmd[i] = to_var(mini, cmd->cmd[i]);
			//printf("%s\n", cmd->cmd[i]);
			i++;
		}
		if (cmd->cmd && ft_strchr(str, PIPE))
			cmd->next = get_cmd(mini, cmd->next, &ft_strchr(str, PIPE)[1], 0);
		// get_path(mini, cmd, str, 0);
	}
	return (cmd);
}
