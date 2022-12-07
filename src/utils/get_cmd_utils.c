/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:25:41 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/07 17:44:45 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

t_cmd	*cmd_init(t_mini *mini, char *str, int i)
{
	t_cmd	*cmd;
	char	*input;

	cmd = malloc (sizeof(t_cmd));
	input = ft_strdup(mini, "");
	if (!cmd || !input)
		return (NULL);
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
	ft_free_tab (cmds, ft_tablen(cmds));
	return (result);
}

char	*delete_double_quotes(t_mini *mini, char *str, int i)
{
	char	*result;

	result = ft_strdup(mini, "");
	if (!result)
		return (NULL);
	while (str[++i] != '"')
	{
		if (str[i] == '$' && str[i + 1] != '"' && str[i + 1] != ' ')
			result = ft_strjoin(mini, result, ft_var(mini, &str[i + 1]));
		else
			result = ft_strjoin2(mini, result, str[i]);
	}
	return (result);
}

char	*delete_quotes(t_mini *mini, char *str, int i, int j)
{
	char	*result;
	int		len;

	len = ft_strlen(str);
	result = malloc (sizeof(char) * len);
	if (!result)
		ft_error(mini, MALLOC_ERR, EXIT);
	while (str[++i] != S_QUOTE)
		result[j++] = str[i];
	result[j] = '\0';
	free (str);
	return (result);
}

char	*get_vars(t_mini *mini, char *str, int i, char *result)
{
	char	c;

	result = ft_strdup(mini, "");
	if (!result)
		return (NULL);
	while (str[++i])
	{
		if (str[i] && str[i] == S_QUOTE)
			result = ft_strjoin3(result, delete_quotes(&str[i], 0, 0, 0));
		else if (str[i] && str[i] == '"')
			result = ft_strjoin(mini, result,
					delete_double_quotes(mini, &str[i], 0));
		else if (str[i] && str[i] == '$' && str[i + 1] != ' ')
			result = ft_strjoin(mini, result, ft_var(mini, &str[i + 1]));
		if (str[i] == '$')
			c = ' ';
		else if (str[i] == '"' || str[i] == S_QUOTE)
			c = str[i];
		while (str[++i] && str[i] != c)
			i++;
		while (str[i] && str[i] != S_QUOTE && str[i] != '"' && str[i] != '$')
			result = ft_strjoin2(mini, result, str[i++]);
	}
	free (str);
	return (result);
}

// char	*manage_string(t_mini *mini, char *str, int i)
// {
// 	char	**parts;
// 	char	*result;

// 	result = NULL;
// 	if (i == 0)
// 	{
// 		result = ft_strdup(str);
// 		free (str);
// 	}
// 	else if (i == 1)
// 		result = ft_strdup2(str);
// 	parts = split_string(result, 0, 0, 0);
// 	// int	n;
// 	// n = 0;
// 	// while (parts && parts[n])
// 	// 	printf("%s\n", parts[n++]);
// 	parts = transform_parts(mini, parts, 0, 0);
// 	result = join_parts(parts, result, 0);
// 	return (result);
// }
