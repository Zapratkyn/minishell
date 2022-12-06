/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:25:41 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/06 15:55:43 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

t_cmd	*cmd_init(t_mini *mini, char *str, int i)
{
	t_cmd	*cmd;
	char	*input;

	cmd = malloc (sizeof(t_cmd));
	if (!cmd)
		ft_error(mini, MALLOC_ERR, EXIT);
	input = ft_strdup(mini, "");
	cmd->path = NULL;
	cmd->cmds = NULL;
	cmd->infile = STDIN_FILENO;
	while (str[i] && str[i] != PIPE)
		input = ft_strjoin2(mini, input, str[i++]);
	cmd->infile = mini_heredoc(mini, input, cmd->infile);
	if (input)
		free (input);
	cmd->outfile = STDOUT_FILENO;
	cmd->pid = -1;
	cmd->cmds = ft_split_cmd(mini, str, 0, 0);
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

char	**clean_files(t_mini *mini, char **cmds, int i, int j)
{
	char	**result;
	int		len;

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
	free (cmds);
	return (result);
}

// char	*delete_double_quotes(char *str, int i, int j, int len)
// {
// 	char	*result;

// 	while (str[i])
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
// 	free (str);
// 	result[len] = '\0';
// 	return (result);
// }

char	*manage_string(t_mini *mini, char *str, int i)
{
	char	**parts;
	char	*result;

	result = NULL;
	if (!i)
	{
		result = ft_strdup(mini, str);
		free (str);
	}
	else if (i == 1)
		result = ft_strdup2(mini, str);
	parts = split_string(mini, result, 0, 0);
	parts = transform_parts(mini, parts, 0, 0);
	ft_put_tab(parts);
	result = fill_parts(mini, parts, result, 0);
	return (result);
}
