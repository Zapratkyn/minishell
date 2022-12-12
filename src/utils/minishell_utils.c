/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:24:11 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/12 15:15:10 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

int	is_input(char *str)
{
	int		i;

	i = 0;
	if (ft_strlen(str) == 0 || ft_quotes(str, -1, 0, 0) == -1)
		return (0);
	if (str[0] == '/' && (!str[1] || str[1] == ' '))
	{
		ft_putendl_fd("/: is a directory", 2);
		g_status = 126;
		return (0);
	}
	if (str[0] == '/' && !dir(str, 0, 0, 0))
		return (0);
	while (str[i])
	{
		if (str[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

void	mini_new_line(int sig)
{
	(void)sig;
	g_status = 1;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
}

int	ft_quotes(char *str, int i, int quotes, int double_quotes)
{
	while (str[++i])
	{
		if (str[i] == '"')
		{
			i++;
			double_quotes++;
			while (str [i] && str[i] != '"')
				i++;
			if (str[i] == '"')
				double_quotes++;
		}
		else if (str[i] == S_QUOTE)
		{
			i++;
			quotes++;
			while (str[i] && str[i] != S_QUOTE)
				i++;
			if (str[i] == S_QUOTE)
				quotes++;
		}
	}
	if ((quotes % 2) != 0 || (double_quotes % 2) != 0)
		return (unclosed_quotes());
	return (1);
}

int	ft_pipes(char *str, int i)
{
	if (str[0] == PIPE)
	{
		ft_putendl_fd("syntax error near unexpected token `|'", 2);
		return (1);
	}
	if (str[ft_strlen(str) - 1] == PIPE)
	{
		ft_putendl_fd("Unclosed pipes forbidden in minishell", 2);
		return (1);
	}
	while (str[i])
	{
		if (str[i] == PIPE)
		{
			ft_putendl_fd("syntax error near unexpected token `|'", 2);
			return (1);
		}
		while (str[i] && str[i] != PIPE)
			i++;
	}
	return (0);
}

int	quotes(char *str, char c, int i)
{
	c = str[i++];
	while (str[i] != c)
		i++;
	return (i + 1);
}
