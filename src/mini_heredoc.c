/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 15:09:46 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/13 15:36:23 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

void	manage_eof(t_mini *mini, char *str, int i)
{
	char	c;

	mini->tempstr2 = ft_strdup(mini, "");
	while (str[i])
	{
		if (str[i] == S_QUOTE || str[i] == '"')
		{
			c = str[i++];
			while (str[i] != c)
				mini->tempstr2 = ft_strjoin2(mini, mini->tempstr2, str[i++]);
			i++;
		}
		else
			mini->tempstr2 = ft_strjoin2(mini, mini->tempstr2, str[i++]);
	}
}

int	fill_fd(t_mini *mini, char *input, int fd, char *str)
{
	int		mode;

	mode = 0;
	if (!ft_strchr(str, '"') && !ft_strchr(str, S_QUOTE))
		mode = 1;
	manage_eof(mini, str, 0);
	if (!input || end_of_heredoc(input, mini->tempstr2))
	{
		if (input)
			free (input);
		close (fd);
		free (mini->tempstr2);
		mini->tempstr2 = NULL;
		return (0);
	}
	else
	{
		if (mode == 1)
			input = get_vars(mini, input, 0);
		write (fd, input, ft_strlen(input));
		write (fd, "\n", 1);
		free (input);
		free (mini->tempstr2);
		mini->tempstr2 = NULL;
		return (1);
	}
}

void	add_heredoc(t_mini *mini, int i)
{
	int		fd;
	char	*nb;

	nb = ft_itoa(mini, i);
	mini->tempstr = ft_strjoin(mini, ft_strdup(mini, "/tmp/heredoc_"), nb);
	free (nb);
	while (!access(mini->tempstr, F_OK))
	{
		i++;
		free (mini->tempstr);
		mini->tempstr = NULL;
		nb = ft_itoa(mini, i);
		mini->tempstr = ft_strjoin(mini, ft_strdup(mini, "/tmp/heredoc_"), nb);
		free (nb);
	}
	fd = open(mini->tempstr, O_CREAT | O_RDWR, 0777);
	close (fd);
}

int	add_fd(t_mini *mini, char *str, int fd)
{
	g_status = 0;
	if (!ft_quotes(str, -1, 0, 0))
		return (unclosed_quotes());
	else if (str[0] == '<' && str[1] && str[1] == '<')
		return (spike_error(mini, &str[2]));
	else if (str[0] == '<' && !str[1])
		return (get_infos_error(mini, NULL, 1, NULL));
	add_heredoc(mini, 1);
	fd = open(mini->tempstr, O_WRONLY);
	if (str[0] == '<' && str[1] && str[1] != '<')
		return (eof_to_fd(mini, &str[1], fd, mini->tempstr));
	while (1)
	{
		signal(SIGINT, mini_new_line);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
		if (g_status == 1 || !fill_fd(mini, readline("> "), fd, str))
			break ;
	}
	if (g_status == 1)
		return (-1);
	fd = open(mini->tempstr, O_RDONLY);
	free (mini->tempstr);
	mini->tempstr = NULL;
	return (fd);
}

int	mini_heredoc(t_mini *mini, t_cmd *cmd, int fd, int i)
{
	char	*eof;

	while (cmd->cmds[i] && fd != -1)
	{
		if (cmd->cmds[i][0] == '<')
		{
			fd = STDIN_FILENO;
			if (cmd->cmds[i][1] == '<')
			{
				if (cmd->cmds[i][2])
					eof = &cmd->cmds[i][2];
				else if (!cmd->cmds[i][2] && cmd->cmds[i + 1]
						&& cmd->cmds[i + 1][0] != '<'
						&& cmd->cmds[i + 1][0] != '>')
					eof = cmd->cmds[i + 1];
				else
					return (get_infos_error(mini, cmd, 1, NULL));
				fd = add_fd(mini, eof, 0);
			}
		}
		i++;
	}
	return (fd);
}
