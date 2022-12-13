/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:25:41 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/13 17:53:26 by gponcele         ###   ########.fr       */
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

void	join_parts(t_mini *mini, int i)
{
	mini->tempstr3 = ft_strdup(mini, "");
	while (mini->temptab && mini->temptab[i])
	{
		if (mini->temptab[i][0] == '$' && mini->temptab[i][1] && (ft_isalnum(mini->temptab[i][1])
			|| mini->temptab[i][1] == '_' || mini->temptab[i][1] == '?'))
			mini->tempstr3 = ft_var(mini, &mini->temptab[i++][1], mini->tempstr3);
		else if (mini->temptab[i][0] == S_QUOTE)
		{
			delete_quotes(mini, mini->temptab[i++], 0, 0);
			mini->tempstr3 = ft_strjoin(mini, mini->tempstr3, mini->tempstr4);
			mini->tempstr4 = ft_free(mini->tempstr4);
		}
		else if (mini->temptab[i][0] == '"')
		{
			delete_double_quotes(mini, mini->temptab[i++], 1);
			mini->tempstr3 = ft_strjoin(mini, mini->tempstr3, mini->tempstr4);
			mini->tempstr4 = ft_free(mini->tempstr4);
		}
		else
			mini->tempstr3 = ft_strjoin(mini, mini->tempstr3, mini->temptab[i++]);
	}
	mini->temptab = ft_free_tab(mini->temptab, ft_tablen(mini->temptab));
}

char	*manage_string(t_mini *mini, char *str, int i)
{
	split_string(mini, str, 0, 0);
	join_parts(mini, 0);
	if (i == 1)
		free (str);
	return (mini->tempstr3);
}

t_cmd	*get_cmd(t_mini *mini, t_cmd *cmd, char *str, int i)
{
	cmd = cmd_init(mini, str);
	get_path(mini, cmd, 0);
	cmd->cmds = clean_files(mini, cmd->cmds, -1, 0);
	while (cmd->cmds && cmd->cmds[++i])
	{
		if (cmd->cmds[i][0] == '$' && cmd->cmds[i][1]
			&& (ft_isalnum(cmd->cmds[i][1]) || cmd->cmds[i][1] == '_'
			|| cmd->cmds[i][1] == '?') && !mini_getenv(mini, &cmd->cmds[i][1])
			&& !mini_get_status(mini, &cmd->cmds[i][1], 1))
			cmd->cmds[i] = ft_free(cmd->cmds[i]);
		else
		{
			cmd->cmds[i] = ft_strdup(mini,
					manage_string(mini, cmd->cmds[i], 1));
			mini->tempstr3 = ft_free(mini->tempstr3);
		}
	}
	if (ft_strchr_minishell(str, PIPE, 0)
		&& cmd->outfile != -1 && ft_strcmp(cmd->path, "none"))
		cmd->next = get_cmd(mini, cmd->next,
				&ft_strchr_minishell(str, PIPE, 0)[1], 0);
	return (cmd);
}
