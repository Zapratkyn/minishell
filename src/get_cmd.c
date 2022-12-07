/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:25:41 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/07 17:36:06 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

char	*ft_var(t_mini *mini, char *str)
{
	if (!is_var(mini, str, 0))
		return ("");
	return (mini_getenv(mini, str));
}

// char	*delete_quotes(char *str, int i, int j)
// {
// 	char	*result;

// 	result = malloc (sizeof(char) * ft_strlen(str) - 1);
// 	if (!result)
// 		return (NULL);
// 	while (str[i] != S_QUOTE)
// 		result[j++] = str[i++];
// 	result[j] = '\0';
// 	return (result);
// }

// char	**transform_parts(t_mini *mini, char **parts, int i, int len)
// {
// 	char	**result;

// 	while (parts[i++])
// 		len++;
// 	result = malloc (sizeof(char *) * len + 1);
// 	if (!result)
// 		return (NULL);
// 	i = 0;
// 	while (parts[i])
// 	{
// 		if (parts[i][0] == '$')
// 			result[i] = ft_strdup(ft_var(mini, &parts[i][1], 1));
// 		else if (parts[i][0] == S_QUOTE)
// 			result[i] = delete_quotes(parts[i], 1, 0);
// 		// else if (parts[i][0] == '"')
// 		// 	result[i] = delete_double_quotes(mini, &parts[i][1], -1);
// 		else
// 			result[i] = ft_strdup(parts[i]);
// 		i++;
// 	}
// 	ft_free_tab(parts);
// 	return (result);
// }

// char	*join_parts(char **parts, char *str, int i)
// {
// 	char	*result;

// 	result = ft_strdup("");
// 	i = 0;
// 	while (parts && parts[i])
// 		result = ft_strjoin(result, parts[i++]);
// 	ft_free_tab(parts);
// 	free (str);
// 	return (result);
// }

char	*to_var(t_mini *mini, char *str)
{
	char	*result;

	result = ft_var(mini, &str[1]);
	free (str);
	return (result);
}

t_cmd	*get_cmd(t_mini *mini, t_cmd *cmd, char *str, int i)
{
	(void)i;
	cmd = cmd_init(mini, str, 0);
	if (cmd && (str[1] || (str[0] != S_QUOTE && str[0] != '"')))
	{
		get_path(mini, cmd, 0);
		cmd->cmds = clean_files(cmd->cmds, -1, 0, 0);
		while (cmd->cmds && cmd->cmds[++i])
		{
			if (cmd->cmds[i][0] == '$')
				cmd->cmds[i] = to_var(mini, cmd->cmds[i]);
			// else
			// 	cmd->cmds[i] = get_vars(mini, cmd->cmds[i], -1, NULL);
			printf("'%s'\n", cmd->cmds[i]);
		}
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
