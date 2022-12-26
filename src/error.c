/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 12:52:19 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/25 14:17:33 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

void	ft_error(t_mini *mini, char *type, int is_exit)
{
	ft_putstr_fd(type, STDERR_FILENO);
	write (STDERR_FILENO, "\n", 1);
	if (is_exit == EXIT)
	{
		if (mini)
			ft_free_all(mini);
		write(STDERR_FILENO, "\nexit\n", 6);
		exit(g_status);
	}
}

int	get_infos_error(t_mini *mini, t_cmd *cmd, int i, char *s)
{
	(void)cmd;
	if (i == 1)
	{
		ft_error(mini, "syntax error near unexpected token", NO_EXIT);
		g_status = 258;
	}
	else if (i == 2)
	{
		mini->tempstr = ft_strjoin(mini,
				ft_strdup(mini, "minishell: cannot open "), s);
		mini->tempstr = ft_strjoin(mini, mini->tempstr,
				": No such file or directory");
		ft_error(mini, mini->tempstr, NO_EXIT);
		mini->tempstr = ft_free(mini->tempstr);
		g_status = 1;
	}
	else if (i == 3)
	{
		mini->tempstr = ft_strjoin(mini,
				ft_strdup(mini, s), " : command not found");
		ft_error(mini, mini->tempstr, NO_EXIT);
		mini->tempstr = ft_free(mini->tempstr);
		g_status = 127;
	}
	return (-1);
}

int	unclosed_quotes(void)
{
	ft_putendl_fd("Unclosed quotes forbidden in minishell", 2);
	g_status = 1;
	return (-1);
}

int	spike_error(t_mini *mini)
{
	ft_error(mini, "syntax error near unexpected token", 0);
	g_status = 258;
	return (-1);
}

int	dir(t_mini *mini, char *str, int i, char c)
{
	mini->tempstr = ft_strdup(mini, "");
	while (str[i] && str[i] != ' ')
	{
		if (str[i] == '"' || str[i] == S_QUOTE)
		{
			c = str[i++];
			while (str[i] != c)
				mini->tempstr = ft_strjoin2(mini, mini->tempstr, str[i++]);
			i++;
		}
		else
			mini->tempstr = ft_strjoin2(mini, mini->tempstr, str[i++]);
	}
	if (access(mini->tempstr, F_OK))
	{
		write (2, mini->tempstr, ft_strlen(mini->tempstr));
		ft_putendl_fd(": No such file or directory", 2);
		g_status = 127;
		free (mini->tempstr);
		mini->tempstr = NULL;
		return (0);
	}
	free (mini->tempstr);
	mini->tempstr = NULL;
	return (1);
}
