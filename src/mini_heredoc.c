/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 15:09:46 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/12 11:32:22 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

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

char	*manage_eof(t_mini *mini, char *str, int i)
{
	char 	*result;
	char	c;

	result = ft_strdup(mini, "");
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] == S_QUOTE || str[i] == '"')
		{
			c = str[i++];
			while (str[i] != c)
				result = ft_strjoin2(mini, result, str[i++]);
			i++;
		}
		else
			result = ft_strjoin2(mini, result, str[i++]);
	}
	return (result);
}

int	fill_fd(t_mini *mini, char *input, int fd, char *str)
{
	char	*eof;
	int		mode;
	
	mode = 0;
	if (!ft_strchr(str, '"') && !ft_strchr(str, S_QUOTE))
		mode = 1;
	eof = manage_eof(mini, str, 0);
	if (!input || (!ft_strncmp(input, eof, ft_strlen(input)) && (ft_strlen(input) == ft_strlen(eof))))
	{
		if (input)
			free (input);
		close (fd);
		free (eof);
		return (0);
	}
	else
	{
		if (mode == 1)
			input = get_vars(mini, input, 0);
		write (fd, input, ft_strlen(input));
		write (fd, "\n", 1);
		free (input);
		free (eof);
		return (1);
	}
}

char	*add_heredoc(t_mini *mini, int i)
{
	int		fd;
	char	*nb;
	char	*file;

	(void)mini;
	nb = ft_itoa(mini, i);
	file = ft_strjoin(mini, ft_strdup(mini, "/tmp/heredoc_"), nb);
	free (nb);
	while (!access(file, F_OK))
	{
		i++;
		free (file);
		nb = ft_itoa(mini, i);
		file = ft_strjoin(mini, ft_strdup(mini, "/tmp/heredoc_"), nb);
		free (nb);
	}
	fd = open(file, O_CREAT | O_RDWR, 0777);
	close (fd);
	return (file);
}

int	eof_to_fd(t_mini *mini, char *str, int fd, char *file)
{
	str = manage_string(mini, str, 0);
	write (fd, str, ft_strlen(str));
	write (fd, "\n", 1);
	free (str);
	close (fd);
	fd = open(file, O_RDONLY);
	return (fd);
}

int	spike_error(t_mini *mini, char *str)
{
	char	*spikes;
	char	*error;
	int		i;

	i = 0;
	spikes = ft_strdup(mini, "<");
	while (str[i] && i < 2 && str[i] == '<')
		spikes = ft_strjoin2(mini, spikes, str[i++]);
	error = ft_strjoin(mini, ft_strdup(mini, "syntax error near unexpected token '"), spikes);
	error = ft_strjoin2(mini, error, S_QUOTE);
	ft_error(mini, error, 0);
	free (spikes);
	free (error);
	return (-1);
}

int	add_fd(t_mini *mini, char *str, int fd)
{
	char	*file;
	
	g_status = 0;
	if (!ft_quotes(str, -1, 0, 0))
		return (unclosed_quotes());
	else if (str[0] == '<' && str[1] && str[1] == '<')
		return (spike_error(mini, &str[2]));
	else if (str[0] == '<' && !str[1])
		return (get_infos_error(mini, NULL, 1, NULL));
	file = add_heredoc(mini, 1);
	fd = open(file, O_WRONLY);
	if (str[0] == '<' && str[1] && str[1] != '<')
		return (eof_to_fd(mini, &str[1], fd, file));
	while (1)
	{
		signal(SIGINT, mini_new_line);
		signal(SIGQUIT, SIG_IGN);
		if (g_status == 1 || !fill_fd(mini, readline("> "), fd, str))
			break ;
	}
	if (g_status == 1)
		return (-1);
	fd = open(file, O_RDONLY);
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
