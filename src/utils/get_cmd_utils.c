/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:25:41 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/13 17:28:38 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

t_cmd	*cmd_init(t_mini *mini, char *str)
{
	t_cmd	*cmd;

	cmd = malloc (sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->path = NULL;
	cmd->cmds = NULL;
	cmd->infile = STDIN_FILENO;
	cmd->outfile = STDOUT_FILENO;
	cmd->pid = -1;
	cmd->next = NULL;
	get_input(mini, str, 0);
	cmd->cmds = ft_split_cmd(mini, mini->tempstr, 0, 0);
	cmd->cmds_nb = ft_tablen(cmd->cmds);
	if (ft_quotes(mini->tempstr, -1, 0, 0) == -1)
		cmd->infile = -1;
	mini->tempstr = ft_free(mini->tempstr);
	cmd->infile = mini_heredoc(mini, cmd, cmd->infile, 0);
	return (cmd);
}

int	to_clean(char *str)
{
	if (str[0] == '<')
	{
		if ((str[1] == '<' && !str[2]) || !str[1])
			return (1);
	}
	else if (str[0] == '>')
	{
		if ((str[1] == '>' && !str[2]) || !str[1])
			return (1);
	}
	return (0);
}

char	**clean_files(t_mini *mini, char **cmds, int i, int j)
{
	int		len;
	char	**result;

	len = 0;
	while (cmds[++i])
	{
		if ((cmds[i][0] != '<' && cmds[i][0] != '>')
			&& !(i > 0 && to_clean(cmds[i - 1])))
			len++;
	}
	result = malloc (sizeof(char *) * len + 1);
	if (!result)
		ft_error(mini, MALLOC_ERR, EXIT);
	i = -1;
	while (cmds[++i])
	{
		if ((cmds[i][0] != '<' && cmds[i][0] != '>')
			&& !(i > 0 && to_clean(cmds[i - 1])))
			result[j++] = ft_strdup(mini, cmds[i]);
	}
	result[j] = NULL;
	ft_free_tab (cmds, ft_tablen(cmds));
	return (result);
}

void	delete_double_quotes(t_mini *mini, char *str, int i)
{
	mini->tempstr4 = ft_strdup(mini, "");
	while (str[i] != '"')
	{
		if (str[i] == '$' && str[i + 1] != '"' && str[i + 1] != ' ')
		{
			i++;
			ft_var(mini, &str[i], mini->tempstr4);
			while (ft_isalnum(str[i]) || str[i] == '_')
				i++;
		}
		else
			mini->tempstr4 = ft_strjoin2(mini, mini->tempstr4, str[i++]);
	}
}

void	delete_quotes(t_mini *mini, char *str, int i, int j)
{
	int		len;

	len = ft_strlen(str);
	mini->tempstr4 = malloc (sizeof(char) * len);
	if (!mini->tempstr4)
		ft_error(mini, MALLOC_ERR, EXIT);
	while (str[++i] != S_QUOTE)
		mini->tempstr4[j++] = str[i];
	mini->tempstr4[j] = '\0';
}
