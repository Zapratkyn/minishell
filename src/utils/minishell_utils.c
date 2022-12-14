/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:24:11 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/14 14:27:43 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

int	is_input2(char *s)
{
	write (2, "minishell: permission denied: ", 30);
	ft_putendl_fd(s, 2);
	free (s);
	g_status = 126;
	return (0);
}

int	is_input(t_mini *mini, char *str, int i, char *s)
{
	int	j;

	while (str[i] == ' ')
		i++;
	j = i;
	if (ft_strlen(str) == 0 || ft_quotes(&str[i], -1, 0, 0) == -1)
	{
		free (s);
		return (0);
	}
	if (str[i] == '/' && str[i + 1] != ' ')
	{
		while (str[++i] == '/')
			s = ft_strjoin2(mini, s, str[i]);
		if (!str[i])
			return (is_input2(s));
	}
	free (s);
	if (str[i] == '/' && !dir(mini, &str[i], 0, 0))
		return (0);
	while (str[++j] != ' ')
		return (1);
	return (0);
}

int	ft_quotes(char *str, int i, int quotes, int double_quotes)
{
	while (str[++i])
	{
		if (str[i] == '"')
		{
			i++;
			double_quotes++;
			while (str[i] && str[i] != '"')
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
	while (str[i])
	{
		while (str[i] && str[i] != PIPE)
			i++;
		if (str[i] && str[i] == PIPE)
		{
			while (str[i] && str[i] != PIPE)
				i++;
			i++;
			if (str[i] == PIPE)
			{
				ft_putendl_fd("syntax error near unexpected token `|'", 2);
				return (1);
			}
		}
	}
	return (0);
}

int	ft_pipes2(char *str, int i)
{
	while (str[i] == ' ')
		i--;
	if (str[i] == PIPE)
	{
		ft_putendl_fd("Pipe as a last character forbidden in minishell", 2);
		return (1);
	}
	i = -1;
	while (str[++i])
	{
		while (str[i] == ' ')
			i++;
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
