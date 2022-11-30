/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 15:09:46 by gponcele          #+#    #+#             */
/*   Updated: 2022/11/30 17:56:38 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

void	heredoc_c(int sig)
{
	(void)sig;
	g_status = 1;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
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

char	*get_input(char *str, int i, char *end, char *result)
{
	char	*input;
	int		check;

	g_status = 0;
	check = 0;
	input = ft_calloc(1, 1);
	while (str[i] == ' ')
		i++;
	while (str[i] && str[i] != ' ')
		end = ft_strjoin2(ft_strdup(end), str[i++]);
	while (1)
	{
		signal(SIGINT, heredoc_c);
		signal(SIGQUIT, SIG_IGN);
		input = (readline("> "));
		check = check_input(input, end);
		if (check < 0 || g_status == 1)
			break ;
		result = ft_strjoin(ft_strdup(result), input);
		result = ft_strjoin2(result, '\n');
		free (input);
	}
	if (g_status == 1 || check == -1 || !end || !result)
		return (NULL);
	return (result);
}

int	add_heredoc(char *input, char *file)
{
	int	i;
	int	fd;

	i = 1;
	file = ft_strjoin(ft_strdup(file), ft_itoa(i));
	while (!access(file, F_OK))
	{
		i++;
		free (file);
		file = ft_strdup("./heredocs/heredoc_");
		file = ft_strjoin(file, ft_itoa(i));
	}
	fd = open(file, O_CREAT | O_RDWR, 0777);
	free (file);
	write (fd, input, ft_strlen(input));
	i++;
	return (fd);
}

int	mini_heredoc(char *str, int fd)
{
	char	*input;

	input = NULL;
	while (ft_strchr(str, '<'))
	{
		str = &ft_strchr(str, '<')[1];
		if (input)
			free (input);
		if (str[0] == '<')
		{
			str = &str[1];
			input = get_input(str, 0, "", "");
			if (!input)
			{
				write (1, " ", 1);
				return (-1);
			}
		}
	}
	if (input)
		fd = add_heredoc(input, "./heredocs/heredoc_");
	return (fd);
}
