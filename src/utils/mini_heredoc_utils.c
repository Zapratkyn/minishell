/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_heredoc_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 12:53:53 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/22 12:23:32 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minish.h"

int	end_of_heredoc(char *input, char *eof)
{
	if (!ft_strncmp(input, eof, ft_strlen(input))
		&& (ft_strlen(input) == ft_strlen(eof)))
		return (1);
	return (0);
}

char	*get_vars(t_mini *mini, char *str, int i)
{
	char	*result;

	result = ft_strdup(mini, "");
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			i++;
			result = ft_var(mini, &str[i], result);
			while (ft_isalnum(str[i]) || str[i] == '_')
				i++;
		}
		else
			result = ft_strjoin2(mini, result, str[i++]);
	}
	free (str);
	return (result);
}

int	eof_to_fd(t_mini *mini, char *str, int fd, char *file)
{
	str = manage_string(mini, str, 0);
	write (fd, str, ft_strlen(str));
	write (fd, "\n", 1);
	free (str);
	close (fd);
	fd = open(file, O_RDONLY);
	free (file);
	return (fd);
}

int	ft_spikes(t_mini *mini, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd && cmd->cmds[i])
	{
		if (cmd->cmds[i][0] == '>' && ((!cmd->cmds[i][1]
			&& (!cmd->cmds[i + 1] || cmd->cmds[i + 1][0] == '<'
			|| cmd->cmds[i + 1][0] == '>'))
			|| (cmd->cmds[i][1] == '>' && !cmd->cmds[i][2]
			&& (!cmd->cmds[i + 1] || cmd->cmds[i + 1][0] == '<'
			|| cmd->cmds[i + 1][0] == '>'))))
			return (spike_error(mini));
		if (ft_strlen(cmd->cmds[0]) == 1
			&& cmd->cmds[0][0] == '<' && !cmd->cmds[1])
			return (spike_error(mini));
		if (!ft_strncmp("<<<<", cmd->cmds[i], 4)
			|| !ft_strncmp(">>>", cmd->cmds[i], 3))
			return (spike_error(mini));
		i++;
	}
	return (1);
}

char	*get_eof(t_cmd *cmd, int i)
{
	if (cmd->cmds[i][2] && cmd->cmds[i][2] == '<'
		&& !cmd->cmds[i][3] && !cmd->cmds[i + 1])
		return (NULL);
	if (cmd->cmds[i][2] && cmd->cmds[i][2] == '<'
		&& !cmd->cmds[i][3] && cmd->cmds[i + 1])
		return (cmd->cmds[i + 1]);
	if (cmd->cmds[i][2] && cmd->cmds[i][2] != '<')
		return (&cmd->cmds[i][2]);
	if (cmd->cmds[i][2] && cmd->cmds[i][2] == '<' && cmd->cmds[i][3])
		return (&cmd->cmds[i][3]);
	else if (!cmd->cmds[i][2] && cmd->cmds[i + 1]
			&& cmd->cmds[i + 1][0] != '<'
			&& cmd->cmds[i + 1][0] != '>')
		return (cmd->cmds[i + 1]);
	return (NULL);
}
