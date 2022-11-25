/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:24:11 by gponcele          #+#    #+#             */
/*   Updated: 2022/11/25 15:36:10 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

char	*mini_getenv(t_mini *mini, char *var)
{
	int	i;
	int	len;

	len = ft_strlen(var);
	i = 0;
	while (ft_strncmp(mini->env[i], var, len) || mini->env[i][len] != '=')
		i++;
	if (!mini->env[i])
		return (NULL);
	return (&mini->env[i][len + 1]);
}

void	mini_exit(t_mini *mini)
{
	if (mini->cmd)
		ft_free_cmd(mini->cmd);
	ft_free_env(mini->var);
	free (mini->prompt);
	printf("\nexit\n");
	exit (0);
}

int	is_input(char *str)
{
	int	i;

	i = 0;
	if (ft_strlen(str) == 0)
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
	write (1, "\n", 1);
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

int	start_with_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == PIPE)
		{
			printf("parse error near '|'\n");
			return (1);
		}
		i++;
	}
	return (0);
}
