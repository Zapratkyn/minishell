/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:25:41 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/02 13:48:40 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

char	*delete_quotes(t_mini *mini, char *str, char c)
{
	char	*result;
	int		i;
	int		j;

	i = 1;
	j = 0;
	result = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!result)
		ft_error(mini, MALLOC_ERR, EXIT);
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
	result = NULL;
	if (!is_var(mini, str, 0))
		return (NULL);
	len = is_var(mini, str, 1);
	result = malloc (sizeof(char) * len + 1);
	if (!result)
		ft_error(mini, MALLOC_ERR, EXIT);
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
		ft_error(mini, MALLOC_ERR, EXIT);
	while (str[++i] != '"')
	{
		if (str[i] == '$' && str[i + 1] != '"' && str[i + 1] != ' ')
		{
			var = ft_var(mini, &str[i + 1]);
			if (var)
			{
				result = ft_strjoin(mini, result, mini_getenv(mini, var));
				i += (ft_strlen(var));
				free (var);
			}
			else
				i += is_var(mini, &str[i + 1], 1);
		}
		else
			result = ft_strjoin2(mini, result, str[i]);
	}
	free (str);
	return (result);
}

char	*get_vars(t_mini *mini, char *str, int i)
{
	char	*result;
	char	*var;

	result = calloc(1, 1);
	if (!result)
		ft_error(mini, MALLOC_ERR, EXIT);
	while (str[++i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] != ' ')
		{
			var = ft_var(mini, &str[i + 1]);
			if (var)
			{
				result = ft_strjoin(mini, result, mini_getenv(mini, var));
				i += (ft_strlen(var));
				free (var);
			}
			else
				i += is_var(mini, &str[i + 1], 1);
		}
		else
			result = ft_strjoin2(mini, result, str[i]);
	}
	free (str);
	return (result);
}

t_cmd	*get_cmd(t_mini *mini, t_cmd *cmd, char *str, int i)
{
	cmd = cmd_init(mini);
	if (cmd && (str[1] || (str[0] != S_QUOTE && str[0] != '"')))
	{
		cmd->cmds = ft_split_cmd(mini, str, 0, 0);
		while (cmd->cmds[++i])
		{
			if (cmd->cmds[i][0] == S_QUOTE)
				cmd->cmds[i] = delete_quotes(mini, cmd->cmds[i], S_QUOTE);
			else if (cmd->cmds[i][0] == '"')
				cmd->cmds[i] = delete_double_quotes(mini, cmd->cmds[i], 0);
			else if (dol(cmd->cmds[i]))
				cmd->cmds[i] = get_vars(mini, cmd->cmds[i], -1);
		}
		get_path(mini, cmd, 0);
		cmd->cmds = clean_files(mini, cmd->cmds, -1, 0);
		if (cmd->cmds && ft_strchr(str, PIPE))
			cmd->next = get_cmd(mini, cmd->next,
					&ft_strchr(str, PIPE)[1], -1);
	}
	return (cmd);
}
