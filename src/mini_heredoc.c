/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 15:09:46 by gponcele          #+#    #+#             */
/*   Updated: 2022/11/30 12:45:03 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

void	heredoc_c(int sig)
{
	(void)sig;
	write (1, "\n", 1);
	g_status = 1;
}

int	check_input(char *str, char *end)
{
	if (!str)
		return (-1);
	else if ((!ft_strncmp(str, end, ft_strlen(end) && ft_strlen(str) == ft_strlen(end))))
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
	while (str[i] != ' ')
		end = ft_strjoin2(end, str[i++]);
	while (g_status == 0)
	{
		signal(SIGINT, heredoc_c);
		signal(SIGQUIT, SIG_IGN);
		input = (readline(">"));
		check = check_input(input, end);
		if (check < 0)
			break ;
		result = ft_strjoin(result, input);
		result = ft_strjoin2(input, '\n');
		free (input);
	}
	if (g_status == 1 || check == -1)
		return (NULL);
	return (result);
}

int	add_heredoc(char *input, char *file)
{
	static int	i = 1;
	int			fd;

	file = ft_strjoin(file, ft_itoa(i));
	fd = open(file, O_CREAT | O_RDONLY, 0777);
	free (file);
	write (fd, input, ft_strlen(input));
	i++;
	return (fd);
}

int	mini_heredoc(char *str, int fd)
{
	char	*input;

	input = NULL;
	while (ft_strnstr(str, "<<", 2))
	{
		if (input)
			free (input);
		str = &ft_strnstr(str, "<<", 2)[2];
		input = get_input(str, 0, "", "");
		if (!input)
			break ;
	}
	if (input)
		fd = add_heredoc(input, "./heredocs/heredoc_");
	return (fd);
}