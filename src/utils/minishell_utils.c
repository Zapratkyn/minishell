/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:24:11 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/12 11:16:49 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

void	mini_exit(t_mini *mini)
{
	if (mini->cmd)
		ft_free_cmd(mini->cmd);
	ft_lstclear(&mini->var);
	ft_free_tab(mini->paths, ft_tablen(mini->paths));
	free (mini->prompt);
	printf("exit\n");
	exit (g_status);
}

int	is_input(char *str)
{
	int	i;

	i = 0;
	if (ft_strlen(str) == 0 || ft_quotes(str, -1, 0, 0) == -1)
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

int	start_with_pipe(t_mini *mini, char *str, int i)
{
	char	*s;

	if (str[0] == PIPE && !str[1])
	{
		ft_error(mini, "syntax error near unexpected token `|'", NO_EXIT);
		g_status = 258;
		return (1);
	}
	if (ft_strlen(str) != 0)
		add_history(str);
	if (!ft_strchr(str, PIPE))
		return (0);
	s = str;
	while (ft_strchr(s, PIPE))
	{
		i = 0;
		s = &ft_strchr(s, PIPE)[1];
		while (s[i] && s[i] != PIPE)
		{
			if (s[i] != ' ')
				return (0);
			i++;
		}
	}
	return (1);
}
