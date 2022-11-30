/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:24:11 by gponcele          #+#    #+#             */
/*   Updated: 2022/11/30 16:00:01 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

void	mini_exit(t_mini *mini)
{
	if (mini->cmd)
		ft_free_cmd(mini->cmd);
	ft_free_env(mini->var);
	free (mini->prompt);
	printf("exit\n");
	exit (g_status);
}

int	is_input(char *str)
{
	int	i;

	i = 0;
	if (ft_strlen(str) == 0 || !ft_quotes(str))
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
	rl_replace_line("", 0);
}

int	ft_quotes(char *str)
{
	int	i;
	int	quotes;
	int	double_quotes;

	i = 0;
	quotes = 0;
	double_quotes = 0;
	while (str[i] && str[i] != 124)
	{
		if (str[i] == '"')
			double_quotes++;
		else if (str[i] == 39)
			quotes++;
		i++;
	}
	if ((quotes % 2) != 0 || (double_quotes % 2) != 0)
		return (0);
	return (1);
}

int	start_with_pipe(char *str, int i)
{
	char	*s;

	if (str[0] == PIPE && !str[1])
	{
		ft_error("syntax error near unexpected token `|'", 0);
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
