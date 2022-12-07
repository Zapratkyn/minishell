/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 12:52:19 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/07 18:11:04 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

int	get_infos_error(t_mini *mini, t_cmd *cmd, int i, char *s)
{
	char	*str;

	str = NULL;
	if (i == 1)
	{
		ft_error(mini, "syntax error near unexpected token `newline'", 0);
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
