/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:25:41 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/08 11:54:06 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

t_cmd	*cmd_init(t_mini *mini, char *str, int i)
{
	t_cmd	*cmd;
	char	*input;

	(void)mini;
	input = ft_strdup("");
	while (str[i] && str[i] != PIPE)
	{
		input = ft_strjoin2(input, str[i++]);
		if (!input)
			return (NULL);
	}
	cmd = malloc (sizeof(t_cmd));
	if (!cmd || !input)
		return (NULL);
	cmd->path = NULL;
	cmd->cmds = NULL;
	cmd->infile = STDIN_FILENO;
	cmd->infile = mini_heredoc(mini, input, cmd->infile, 0);
	cmd->outfile = STDOUT_FILENO;
	cmd->pid = -1;
	cmd->cmds = ft_split_cmd(input, 0, 0, 0);
	if (!cmd->cmds)
		return (NULL);
	cmd->next = NULL;
	free (input);
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

char	**clean_files(char **cmds, int i, int j, int len)
{
	char	**result;

	while (cmds[++i])
	{
		if ((cmds[i][0] != '<' && cmds[i][0] != '>')
			&& !(i > 0 && to_clean(cmds[i - 1])))
			len++;
	}
	result = malloc (sizeof(char *) * len + 1);
	if (!result)
		return (NULL);
	i = -1;
	while (cmds[++i])
	{
		if ((cmds[i][0] != '<' && cmds[i][0] != '>')
			&& !(i > 0 && to_clean(cmds[i - 1])))
			result[j++] = ft_strdup(cmds[i]);
	}
	result[j] = NULL;
	ft_free_tab (cmds);
	return (result);
}

char	*delete_double_quotes(t_mini *mini, char *str, int i)
{
	char	*result;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (str[i] != '"')
	{
		if (str[i] == '$' && str[i + 1] != '"' && str[i + 1] != ' ')
		{
			i++;
			result = ft_var(mini, &str[i], result);
			while (ft_isalnum(str[i]) || str[i] == '_')
				i++;
		}
		else
			result = ft_strjoin2(result, str[i++]);
	}
	return (result);
}

char	*delete_quotes(char *str, int i, int j, int len)
{
	char	*result;

	len = ft_strlen(str);
	result = malloc (sizeof(char) * len);
	if (!result)
		return (NULL);
	while (str[++i] != S_QUOTE)
		result[j++] = str[i];
	result[j] = '\0';
	return (result);
}
