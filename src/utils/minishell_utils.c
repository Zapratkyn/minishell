/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:24:11 by gponcele          #+#    #+#             */
/*   Updated: 2022/11/25 17:38:13 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

char	*mini_getenv(t_mini *mini, char *var)
{
	t_var	*tmp;

	tmp = mini->var;
	while (tmp)
	{
		if (!ft_strncmp(var, tmp->content, ft_strlen(var)))
			return (&tmp->content[ft_strlen(var) + 1]);
		tmp = tmp->next;
	}
	return (NULL);
}

void	mini_exit(t_mini *mini)
{
	if (mini->cmd)
		ft_free_cmd(mini->cmd);
	ft_free_env(mini->var);
	free (mini->prompt);
	printf("\nexit\n");
	exit (g_status);
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
	char	*str;

	(void)sig;
	g_status = 1;
	str = ft_strdup("\nSalut ");
	write (1, str, ft_strlen(str));
	free (str);
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
			ft_error("syntax error near unexpected token `|'", 0);
			g_status = 258;
			return (1);
		}
		i++;
	}
	return (0);
}
