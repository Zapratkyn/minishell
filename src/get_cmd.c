/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:25:41 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/22 17:46:04 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

char	*ft_var(t_mini *mini, char *str, char *result)
{
	if (str[0] == '?')
	{
		mini_get_status(mini, str, 0);
		result = ft_strjoin(mini, result, mini->tempstr5);
		mini->tempstr5 = ft_free(mini->tempstr5);
	}
	else if (mini_getenv(mini, str))
	{
		mini->tempstr5 = ft_strdup(mini, mini_getenv(mini, str));
		result = ft_strjoin(mini, result, mini->tempstr5);
		mini->tempstr5 = ft_free(mini->tempstr5);
	}
	return (result);
}

char	*join_parts(t_mini *mini, char **parts, char *result, int i)
{
	char	*s;

	result = ft_strdup(mini, "");
	while (parts && parts[i])
	{
		if (parts[i][0] == '$' && parts[i][1] && (ft_isalnum(parts[i][1])
			|| parts[i][1] == '_' || parts[i][1] == '?'))
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
	char	*result;
	char	**parts;

	result = NULL;
	parts = split_string(mini, str, 0, 0);
	result = join_parts(mini, parts, NULL, 0);
	if (i == 1)
		free (str);
	return (result);
}

t_cmd	*get_cmd(t_mini *mini, t_cmd *cmd, char *str, int i)
{
	cmd = cmd_init(mini, str);
	if (cmd->infile != -1 && cmd->infile != -2)
	{
		get_path(mini, cmd, NULL, 0);
		cmd->cmds = clean_files(mini, cmd->cmds, -1, 0);
		while (cmd->cmds && cmd->cmds[++i])
			cmd->cmds[i] = manage_string(mini, cmd->cmds[i], 1);
	}
	if (ft_strchr_minishell(str, PIPE, 0))
		cmd->next = get_cmd(mini, cmd->next,
				&ft_strchr_minishell(str, PIPE, 0)[1], 0);
	return (cmd);
}
