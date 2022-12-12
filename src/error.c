/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 12:52:19 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/12 15:30:39 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

void	ft_error(t_mini *mini, char *type, int is_exit)
{
	ft_putstr_fd(type, STDERR_FILENO);
	write (STDERR_FILENO, "\n", 1);
	if (is_exit == EXIT)
	{
		ft_free_all(mini);
		write(STDERR_FILENO, "\nexit\n", 6);
		exit(g_status);
	}
}

int	get_infos_error(t_mini *mini, t_cmd *cmd, int i, char *s)
{
	char	*str;

	str = NULL;
	if (i == 1)
	{
		ft_error(mini, "syntax error near unexpected token", NO_EXIT);
		g_status = 258;
	}
	else if (i == 2)
	{
		str = ft_strjoin(mini, ft_strdup(mini, "3: cannot open "), s);
		str = ft_strjoin(mini, str, ": No such file or directory");
		ft_error(mini, str, NO_EXIT);
		free (str);
		g_status = 1;
	}
	else if (i == 3)
	{
		str = ft_strjoin(mini, ft_strdup(mini, s), " : command not found");
		ft_error(mini, str, NO_EXIT);
		free (str);
		g_status = 127;
		cmd->path = ft_strdup(mini, "none");
	}
	return (-1);
}

int	unclosed_quotes(void)
{
	ft_putendl_fd("Unclosed quotes forbidden in minishell", 2);
	return (-1);
}

int	spike_error(t_mini *mini, char *str)
{
	char	*spikes;
	char	*error;
	int		i;

	i = 0;
	spikes = ft_strdup(mini, "<");
	while (str[i] && i < 2 && str[i] == '<')
		spikes = ft_strjoin2(mini, spikes, str[i++]);
	error = ft_strjoin(mini,
			ft_strdup(mini, "syntax error near unexpected token '"), spikes);
	error = ft_strjoin2(mini, error, S_QUOTE);
	ft_error(mini, error, 0);
	free (spikes);
	free (error);
	return (-1);
}

int	dir(char *str, int i, char c, int j)
{
	char	dir[50];

	while (str[i] && str[i] != ' ')
	{
		if (str[i] == '"' || str[i] == S_QUOTE)
		{
			c = str[i++];
			while (str[i] != c)
				dir[j++] = str[i++];
			i++;
		}
		else
			dir[j++] = str[i++];
	}
	dir[j] = '\0';
	if (access(dir, X_OK))
	{
		write (2, dir, ft_strlen(dir));
		ft_putendl_fd(": No such file or directory", 2);
		g_status = 127;
		return (0);
	}
	return (1);
}
