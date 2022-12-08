/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:25:41 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/08 11:36:36 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

char	*ft_var(t_mini *mini, char *str)
{
	if (!is_var(mini, str, 0))
		return ("");
	return (mini_getenv(mini, str));
}

char	*join_parts(t_mini *mini, char **parts, int i)
{
	char	*result;
	char	*s;

	result = ft_strdup(mini, "");
	while (parts && parts[i])
	{
		if (parts[i][0] == '$')
			result = ft_strjoin(mini, result, ft_var(mini, &parts[i++][1]));
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

char	*manage_string(t_mini *mini, char *str)
{
	char	**parts;
	char	*result;

	result = NULL;
	parts = split_string(mini, str, 0, 0);
	result = join_parts(mini, parts, 0);
	free (str);
	return (result);
}

t_cmd	*get_cmd(t_mini *mini, t_cmd *cmd, char *str, int i)
{
	cmd = cmd_init(mini, str, 0);
	if (cmd && (str[1] || (str[0] != S_QUOTE && str[0] != '"')))
	{
		get_path(mini, cmd, 0);
		cmd->cmds = clean_files(mini, cmd->cmds, -1, 0);
		while (cmd->cmds && cmd->cmds[++i])
			cmd->cmds[i] = manage_string(mini, cmd->cmds[i]);
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
