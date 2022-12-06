/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:25:41 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/06 13:25:38 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

t_cmd	*cmd_init(char *str, int i)
{
	t_cmd	*cmd;
	char	*input;

	cmd = malloc (sizeof(t_cmd));
	input = calloc (1, 1);
	if (!cmd || !input)
		return (NULL);
	cmd->path = NULL;
	cmd->cmds = NULL;
	cmd->infile = STDIN_FILENO;
	while (str[i] && str[i] != PIPE)
	{
		input = ft_strjoin2(input, str[i++]);
		if (!input)
			return (NULL);
	}
	cmd->infile = mini_heredoc(input, cmd->infile);
	free (input);
	cmd->outfile = STDOUT_FILENO;
	cmd->pid = -1;
	cmd->cmds = ft_split_cmd(str, 0, 0, 0);
	if (!cmd->cmds || cmd->infile == -1)
		return (NULL);
	cmd->next = NULL;
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
	free (cmds);
	return (result);
}

// char	*delete_double_quotes(char *str, int i, int j, int len)
// {
// 	char	*result;

// 	while (str && str[i])
// 	{
// 		if (str[i] != '"')
// 			len++;
// 		i++;
// 	}
// 	result = malloc (sizeof(char) * len + 1);
// 	if (!result)
// 		return (NULL);
// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] != '"')
// 			result[j++] = str[i];
// 		i++;
// 	}
// 	result[len] = '\0';
// 	return (result);
// }

char	*manage_string(t_mini *mini, char *str, int i)
{
	char	**parts;
	char	*result;

	result = NULL;
	if (i == 0)
	{
		result = ft_strdup(str);
		free (str);
	}
	else if (i == 1)
		result = ft_strdup2(str);
	parts = split_string(result, 0, 0, 0);
	parts = transform_parts(mini, parts, 0, 0);
	result = fill_parts(parts, result, 0);
	return (result);
}