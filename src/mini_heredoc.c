/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 15:09:46 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/08 11:59:10 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

char	*get_vars(t_mini *mini, char *str, int i)
{
	char	*result;

	result = ft_strdup("");
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
			result = ft_strjoin2(result, str[i++]);
	}
	free (str);
	return (result);
}

char	*manage_eof(t_mini *mini, char *str, int i, int len)
{
	char 	*result;
	int		j;

	(void)mini;
	while (str[++i])
	{
		if (str[i] != '"' && str[i] != S_QUOTE)
			len++;
	}
	result = malloc (sizeof(char) * len + 1);
	if (!result)
		return (NULL);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] != '"' && str[i] != S_QUOTE)
			result[j++] = str[i];
	}
	result[j] = '\0';
	return (result);
}

int	fill_fd(t_mini *mini, char *input, int fd, char *str)
{
	char	*eof;
	int		mode;
	
	mode = 0;
	if (!ft_strchr(str, '"') && !ft_strchr(str, S_QUOTE))
		mode = 1;
	eof = manage_eof(mini, str, -1, 0);
	if (!input || (!strncmp(input, eof, ft_strlen(input)) && (ft_strlen(input) == ft_strlen(eof))))
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
	nb = ft_itoa(i);
	file = ft_strjoin(ft_strdup("/tmp/heredoc_"), nb);
	free (nb);
	while (!access(file, F_OK))
	{
		i++;
		free (file);
		nb = ft_itoa(i);
		file = ft_strjoin(ft_strdup("/tmp/heredoc_"), nb);
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

int	spike_error(void)
{
	ft_error("syntax error near unexpected token '<'", 0);
	return (-1);
}

int	add_fd(t_mini *mini, char *str, int fd)
{
	char	*file;
	
	// g_status = 0;
	if (!ft_quotes(str, -1, 0, 0))
		return (unclosed_quotes());
	else if (str[0] == '<' && str[1] && str[1] == '<')
		return (spike_error());
	else if (str[0] == '<' && !str[1])
		return (get_infos_error(NULL, 1, NULL));
	file = add_heredoc(mini, 1);
	fd = open(file, O_WRONLY);
	if (str[0] == '<' && str[1] && str[1] != '<')
		return (eof_to_fd(mini, &str[1], fd, file));
	while (1)
	{
		signal(SIGINT, mini_new_line);
		signal(SIGQUIT, SIG_IGN);
		if (!fill_fd(mini, readline("> "), fd, str))
			break ;
	}
	// if (g_status == 1)
	// 	return (-1);
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
					return (get_infos_error(cmd, 1, NULL));
				fd = add_fd(mini, eof, 0);
			}
		}
		i++;
	}
	return (fd);
}
