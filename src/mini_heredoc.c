/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 15:09:46 by gponcele          #+#    #+#             */
/*   Updated: 2022/11/29 17:12:17 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

void	heredoc_c(int sig)
{
	(void)sig;
	write (1, "\n", 1);
	g_status = 1;
}

int	mini_parser_heredoc(char *input, char *end)
{
	if (!input || (!ft_strncmp(input, end, ft_strlen(end) && ft_strlen(input) == ft_strlen(end))))
		return (0);
}

int	add_heredoc(char *str, int i, char *end)
{
	char *input;

	g_status = 0;
	while (str[i] == ' ')
		i++;
	while (str[i] != ' ')
		end = ft_strjoin2(end, str[i++]);
	while (g_status == 0)
	{
		signal(SIGINT, heredoc_c);
		signal(SIGQUIT, SIG_IGN);
		input = mini_parser_heredoc(readline(">"), end);
		if (!input)
			break ;
	}
}

int	mini_heredoc(char *str, int i, int j)
{
	while (str[++i])
	{
		if (str[i] == '<' && str[i + 1] == '<')
			j = add_heredoc(&str[i + 2], 0, "");
	}
	return (j);
}