/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 15:09:46 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/08 11:27:25 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

char	*get_eof(t_mini *mini, char *str, char *eof)
{
	int		i;
	char	c;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i])
		eof = ft_strdup(mini, "");
	while (str[i] && str[i] != ' ')
	{
		if (str[i] == S_QUOTE || str[i] == '"')
		{
			c = str[i++];
			while (str[i] != c)
				i++;
			i++;
		}
		else
			eof = ft_strjoin2(mini, eof, str[i++]);
	}
	return (eof);
}

char	*get_vars(t_mini *mini, char *str, int i)
{
	char	*result;

	result = ft_strdup(mini, "");
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '"' && str[i + 1] != ' ')
		{
			i++;
			result = ft_strjoin(mini, result, ft_var(mini, &str[i]));
			while (ft_isalnum(str[i]) || str[i] == '_')
				i++;
		}
		else
			result = ft_strjoin2(mini, result, str[i++]);
	}
	free (str);
	return (result);
}

char	*manage_line(t_mini *mini, char *str, char *eof)
{
	if (!ft_strchr(eof, '"') && !ft_strchr(eof, S_QUOTE))
	{
		str = get_vars(mini, str, 0);
		return (str);
	}
	else if ((ft_strchr(eof, '"') || ft_strchr(eof, S_QUOTE)) && ft_quotes(eof, -1, 0, 0))
		return (str);
	return (0);
}

int	fill_fd(t_mini *mini, char *input, int fd, char *eof)
{
	if (!input)
		return (0);
	else if (!ft_strncmp(input, eof, ft_strlen(input)) && (ft_strlen(input) == ft_strlen(eof)))
	{
		free (input);
		free (eof);
		eof = NULL;
		return (0);
	}
	else
	{
		input = manage_line(mini, input, eof);
		write (fd, input, ft_strlen(input));
		write (fd, "\n", 1);
		free (input);
		return (1);
	}
}

int	manage_fd(t_mini *mini, int fd, char *eof)
{
	while (1)
	{
		signal(SIGINT, mini_new_line);
		signal(SIGQUIT, SIG_IGN);
		if (g_status == 1 || !fill_fd(mini, readline("> "), fd, eof))
			break ;
	}
	if (eof)
	{
		free (eof);
		return (-1);
	}
	return (fd);
}

int	add_heredoc(t_mini *mini)
{
	int		i;
	int		fd;
	char	*nb;
	char	*file;

	i = 1;
	nb = ft_itoa(mini, i);
	file = ft_strjoin(mini, ft_strdup(mini, "/tmp/mini_heredocs/heredoc_"), nb);
	free (nb);
	while (!access(file, F_OK))
	{
		i++;
		free (file);
		nb = ft_itoa(mini, i);
		file = ft_strjoin(mini, ft_strdup(mini, "/tmp/mini_heredocs/heredoc_"), nb);
		free (nb);
	}
	fd = open(file, O_CREAT | O_RDWR, 0777);
	free (file);
	return (fd);
}

int	mini_heredoc(t_mini *mini, char *str, int fd)
{
	char	*eof;
	int		i;

	i = 0;
	while (str[i])
	{
		if ((i == 0 && str[i] == '<') || (i > 0 && str[i - 1] == ' '))
		{
			fd = STDIN_FILENO;
			if (str[++i] == '<')
			{
				if (str[i + 1] == '<')
					return (-1);
				eof = get_eof(mini, &str[i + 1], NULL);
				if (!eof)
					return (-1);
				fd = add_heredoc(mini);
				fd = manage_fd(mini, fd, eof);
				if (fd == -1)
					return (fd);
			}
		}
		else
			i++;
	}
	return (fd);
}