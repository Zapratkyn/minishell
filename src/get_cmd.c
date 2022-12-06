/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:25:41 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/06 13:47:24 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

char	*ft_var(t_mini *mini, char *str)
{
	if (!is_var(mini, str, 0))
		return ("");
	return (mini_getenv(mini, str));
}

char	*delete_quotes(t_mini *mini, char *str, int i, int j)
{
	char	*result;

	result = malloc (sizeof(char) * ft_strlen(str) - 1);
	if (!result)
		ft_error(mini, MALLOC_ERR, EXIT);;
	while (str[i] != S_QUOTE)
		result[j++] = str[i++];
	result[j] = '\0';
	return (result);
}

char	**transform_parts(t_mini *mini, char **parts, int i, int len)
{
	char	**result;

	while (parts[i++])
		len++;
	result = malloc (sizeof(char *) * len + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (parts[i])
	{
		if (parts[i][0] == '$')
			result[i] = ft_strdup(mini, ft_var(mini, &parts[i][1]));
		else if (parts[i][0] == S_QUOTE)
			result[i] = delete_quotes(mini, parts[i], 1, 0);
		else
			result[i] = ft_strdup(mini, parts[i]);
		i++;
	}
	ft_free_tab(parts, ft_tablen(parts));
	return (result);
}

char	*fill_parts(t_mini *mini, char **parts, char *str, int i)
{
	char	*result;
	int		j[2];
	int		k;

	while (parts && parts[i])
		j[0] += ft_strlen(parts[i++]);
	printf("\n\nj[0] = '%d'\n\n", j[0]);
	result = malloc (sizeof(char) * (j[0] + 1));
	if (!result)
		ft_error(mini, MALLOC_ERR, EXIT);
	i = -1;
	j[1] = 0;
	while (parts[++i])
	{
		k = 0;
		while (parts[i][k])
			result[j[1]++] = parts[i][k++];
	}
	ft_free_tab(parts, ft_tablen(parts));
	free (str);
	result[j[0]] = '\0';
	return (result);
}

t_cmd	*get_cmd(t_mini *mini, t_cmd *cmd, char *str, int i)
{
	cmd = cmd_init(mini, str, 0);
	if (cmd && (str[1] || (str[0] != S_QUOTE && str[0] != '"')))
	{
		while (cmd->cmds[++i])
		{
			cmd->cmds[i] = manage_string(mini, cmd->cmds[i], 0);
			printf("'%s'\n", cmd->cmds[i]);
		}
		get_path(mini, cmd, 0);
		cmd->cmds = clean_files(mini, cmd->cmds, -1, 0);
		if (cmd->cmds && ft_strchr(str, PIPE))
		{
			cmd->next = get_cmd(mini, cmd->next,
					&ft_strchr(str, PIPE)[1], -1);
			if (!cmd->next)
				return (NULL);
		}
	}
	return (cmd);
}
