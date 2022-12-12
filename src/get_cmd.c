/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:25:41 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/12 16:51:42 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

char	*ft_var(t_mini *mini, char *str, char *result)
{
	char	*s;

	s = NULL;
	if (!is_var(mini, str))
		return (result);
	else if (str[0] == '?')
	{
		s = mini_getenv(mini, str);
		result = ft_strjoin(mini, result, s);
		free (s);
	}
	else
		result = ft_strjoin(mini, result, mini_getenv(mini, str));
	return (result);
}

char	*join_parts(t_mini *mini, char **parts, int i)
{
	char	*result;
	char	*s;

	result = ft_strdup(mini, "");
	while (parts && parts[i])
	{
		if (parts[i][0] == '$' && parts[i][1])
			result = ft_var(mini, &parts[i++][1], result);
		else if (parts[i][0] == S_QUOTE)
		{
			s = delete_quotes(mini, parts[i++], 0, 0);
			result = ft_strjoin(mini, result, s);
			free (s);
		}
		else if (parts[i][0] == '"')
		{
			s = delete_double_quotes(mini, parts[i++], 1);
			result = ft_strjoin(mini, result, s);
			free (s);
		}
		else
			result = ft_strjoin(mini, result, parts[i++]);
	}
	ft_free_tab(parts, ft_tablen(parts));
	return (result);
}

char	*manage_string(t_mini *mini, char *str, int i)
{
	char	**parts;
	char	*result;

	result = NULL;
	parts = split_string(mini, str, 0, 0);
	result = join_parts(mini, parts, 0);
	if (i == 1)
		free (str);
	return (result);
}

t_cmd	*get_cmd(t_mini *mini, t_cmd *cmd, char *str, int i)
{
	cmd = cmd_init(mini, str, 0);
	if (cmd->infile != -1)
	{
		get_path(mini, cmd, 0);
		cmd->cmds = clean_files(mini, cmd->cmds, -1, 0);
		while (cmd->cmds && cmd->cmds[++i])
		{
			// if (cmd->cmds[i][0] == '$' && !is_var(mini, &cmd->cmds[i][1]))
			// 	free (cmd->cmds[i]);
			// else
				cmd->cmds[i] = manage_string(mini, cmd->cmds[i], 1);
		}
		if (ft_strchr(str, PIPE) && cmd->infile != -1
			&& cmd->outfile != -1 && ft_strcmp(cmd->path, "none"))
			cmd->next = get_cmd(mini, cmd->next,
					&ft_strchr(str, PIPE)[1], -1);
	}
	return (cmd);
}
