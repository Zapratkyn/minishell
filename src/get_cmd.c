/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:25:41 by gponcele          #+#    #+#             */
/*   Updated: 2022/11/23 15:54:47 by gponcele         ###   ########.fr       */
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
	char	*index;
	char	*var;
	
	result = malloc(sizeof(char) * 1);
	if (!result)
		return (NULL);
	index = &str[1];
	while (index[i] != '"')
	{
		if (index[i] == '$')
		{
			var = ft_var(mini, &index[i + 1]);
			if (var)
			{
				result = ft_strjoin(result, mini_getenv(mini, var));
				i += (ft_strlen(var) + 1);
				free (var);
			}
			else
				i += is_var(mini, &index[i + 1], 1);
		}
		else
			result = ft_strjoin2(result, index[i++]);
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

void	get_cmd(t_mini *mini, t_cmd *cmd, char *str, int i)
{
	cmd = malloc (sizeof(t_cmd));
	if (cmd)
	{
		cmd->full_cmd = ft_split_cmd(str, 0, 0);
		while (cmd->full_cmd[i])
		{
			if (cmd->full_cmd[i][0] == S_QUOTE)
				cmd->full_cmd[i] = delete_quotes(cmd->full_cmd[i], S_QUOTE);
			else if (cmd->full_cmd[i][0] == '"')
				cmd->full_cmd[i] = delete_double_quotes(mini, cmd->full_cmd[i], 0);
			else if (cmd->full_cmd[i][0] == '$' && !is_var(mini, &cmd->full_cmd[i][1], 0))
				cmd->full_cmd[i] = to_empty(cmd->full_cmd[i]);
			else if (cmd->full_cmd[i][0] == '$' && is_var(mini, &cmd->full_cmd[i][1], 0))
				cmd->full_cmd[i] = to_var(mini, cmd->full_cmd[i]);
			if (cmd->full_cmd[i])
				printf("%s\n", cmd->full_cmd[i]);
			i++;
		}
		if (cmd->full_cmd && ft_strchr(str, PIPE))
			get_cmd(mini, cmd->next, &ft_strchr(str, PIPE)[1], 0);
	}
	// get_path(mini, cmd, str, 0);
}
