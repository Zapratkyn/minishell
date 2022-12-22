/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 15:09:46 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/22 17:27:23 by gponcele         ###   ########.fr       */
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
		mini->tempstr2 = ft_free(mini->tempstr2);
		return (0);
	}
	else
	{
		if (mode == 1)
			input = get_vars(mini, input, 0);
		write (fd, input, ft_strlen(input));
		write (fd, "\n", 1);
		free (input);
		mini->tempstr2 = ft_free(mini->tempstr2);
		return (1);
	}
}

char	*add_heredoc(t_mini *mini, int i)
{
	int		fd;
	char	*nb;
	char	*file;

	g_status = 0;
	nb = ft_itoa(mini, i);
	file = ft_strjoin(mini, ft_strdup(mini, "/tmp/heredoc_"), nb);
	free (nb);
	while (!access(file, F_OK))
	{
		i++;
		file = ft_free(file);
		nb = ft_itoa(mini, i);
		file = ft_strjoin(mini, ft_strdup(mini, "/tmp/heredoc_"), nb);
		free (nb);
	}
	fd = open(file, O_CREAT | O_RDWR, 0777);
	close (fd);
	return (file);
}

int	add_fd(t_mini *mini, char *str, char *eof, int fd)
{
	char	*file;

	if (!ft_quotes(eof, -1, 0, 0))
		return (unclosed_quotes());
	file = add_heredoc(mini, 1);
	fd = open(file, O_WRONLY);
	if (str[2] == '<')
		return (eof_to_fd(mini, eof, fd, file));
	while (1)
	{
		signal(SIGINT, mini_new_line);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
		if (g_status == 1 || !fill_fd(mini, readline("> "), fd, eof))
			break ;
	}
	close (fd);
	if (g_status == 1)
	{
		free (file);
		return (-1);
	}
	fd = open(file, O_RDONLY);
	free (file);
	return (fd);
}

int	mini_heredoc(t_mini *mini, t_cmd *cmd, int fd, int i)
{
	char	*eof;
	int		fd_c;

	fd_c = fd;
	while (cmd->cmds[++i] && fd != -1)
	{
		if (cmd->cmds[i][0] == '<')
		{
			fd = STDIN_FILENO;
			if (cmd->cmds[i][1] == '<')
			{
				eof = get_eof(cmd, i);
				if (!eof)
					return (get_infos_error(mini, cmd, 1, NULL));
				else if (eof[1] != '<')
					fd = add_fd(mini, cmd->cmds[i], eof, 0);
			}
		}
	}
	if (fd_c != STDIN_FILENO)
		return (fd_c);
	return (fd);
}
