/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:25:41 by gponcele          #+#    #+#             */
/*   Updated: 2022/11/29 13:12:19 by ademurge         ###   ########.fr       */
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
	result = NULL;
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
		if (str[i] == '$' && str[i + 1] != '"' && str[i + 1] != ' ')
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
	free (str);
	return (result);
}

char	*get_vars(t_mini *mini, char *str, int i)
{
	char	*result;
	char	*var;

	result = calloc(1, 1);
	if (!result)
		return (NULL);
	while (str[++i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] != ' ')
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
	free (str);
	return (result);
}

t_cmd	*get_cmd(t_mini *mini, t_cmd *cmd, char *str, int i)
{
	printf("%s\n", str);
	cmd = cmd_init();
	if (cmd && (str[1] || (str[0] != S_QUOTE && str[0] != '"')))
	{
		cmd->cmds = ft_split_cmd(str, 0, 0, 0);
		while (cmd->cmds[++i])
		{
			if (cmd->cmds[i][0] == S_QUOTE)
				cmd->cmds[i] = delete_quotes(cmd->cmds[i], S_QUOTE);
			else if (cmd->cmds[i][0] == '"')
				cmd->cmds[i] = delete_double_quotes(mini, cmd->cmds[i], 0);
			else if (dol(cmd->cmds[i]))
				cmd->cmds[i] = get_vars(mini, cmd->cmds[i], -1);
			printf("'%s'\n", cmd->cmds[i]);
		}
		get_path(mini, cmd, 0);
		cmd->cmds = clean_files(cmd->cmds, -1, 0, 0);
		// printf("%s\n", &ft_strchr(str, PIPE)[1]);
		if (cmd->cmds && ft_strchr(str, PIPE))
			cmd->next = get_cmd(mini, cmd->next,
					&ft_strchr(str, PIPE)[1], 0);
	}
	return (cmd);
}
