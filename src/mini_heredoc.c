/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 15:09:46 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/06 13:09:14 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

char	*get_end(t_mini *mini, char *str, char *end)
{
	int		i;

	i = 0;
	while (str[i] == ' ')
		i++;
	while (str[i] && str[i] != ' ')
		end = ft_strjoin2(mini, ft_strdup(mini, end), str[i++]);
	return (end);
}

int	check_input(char *str, char *end)
{
	if (!str)
		return (-1);
	else if ((!ft_strncmp(str, end, ft_strlen(end))
			&& ft_strlen(str) == ft_strlen(end)))
		return (-2);
	return (1);
}

int	add_heredoc(t_mini *mini, char *file)
{
	int		i;
	int		fd;

	i = 1;
	file = ft_strjoin(mini, ft_strdup(mini, file), ft_itoa(mini, i));
	while (!access(file, F_OK))
	{
		i++;
		free (file);
		file = ft_strdup(mini, "/tmp/mini_heredocs/heredoc_");
		file = ft_strjoin(mini, file, ft_itoa(mini, i));
	}
	fd = open(file, O_CREAT | O_RDWR, 0777);
	free (file);
	return (fd);
}

int	get_input(t_mini *mini, char *str, char *end, int fd)
{
	char	*input;
	int		check;

	g_status = 0;
	check = 0;
	input = ft_calloc(mini, 1, 1);
	fd = add_heredoc(mini, "/tmp/mini_heredocs/heredoc_");
	end = get_end(mini, str, "");
	while (1)
	{
		signal(SIGINT, mini_new_line);
		signal(SIGQUIT, SIG_IGN);
		input = (readline("> "));
		check = check_input(input, end);
		if (check < 0 || g_status == 1)
			break ;
		write (fd, input, ft_strlen(input));
		write (fd, "\n", 1);
		free (input);
	}
	if (g_status == 1 || check == -1 || !end)
		return (0);
	return (fd);
}

int	mini_heredoc(t_mini *mini, char *str, int fd)
{
	while (ft_strchr(str, '<'))
	{
		str = &ft_strchr(str, '<')[1];
		fd = STDIN_FILENO;
		if (str[0] == '<')
		{
			str = &str[1];
			fd = get_input(mini, str, "", 0);
			if (fd == 0)
			{
				write (1, "", 1);
				return (-1);
			}
		}
	}
	return (fd);
}
