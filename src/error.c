/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 12:52:19 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/07 12:42:26 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

void	ft_error(char *type, int is_exit)
{
	ft_putstr_fd(type, STDERR_FILENO);
	write (STDERR_FILENO, "\n", 1);
	if (is_exit == 1)
		exit (0);
}

int	get_infos_error(t_cmd *cmd, int i, char *s)
{
	char	*str;

	str = NULL;
	if (i == 1)
	{
		ft_error("syntax error near unexpected token `newline'", 0);
		// g_status = 258;
	}
	else if (i == 2)
	{
		str = ft_strjoin(ft_strdup("3: cannot open "), s);
		str = ft_strjoin(str, ": No such file or directory");
		ft_error(str, 0);
		free (str);
		// g_status = 1;
	}
	else if (i == 3)
	{
		str = ft_strjoin(ft_strdup(s), " : command not found");
		ft_error(str, 0);
		free (str);
		// g_status = 127;
		cmd->path = ft_strdup("none");
	}
	return (-1);
}

int	unclosed_quotes(void)
{
	printf("Unclosed quotes forbidden in minishell\n");
	return (-1);
}
