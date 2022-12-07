/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 16:55:54 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/07 16:42:56 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minish.h"

static unsigned long long	ft_atoull(const char *str)
{
	unsigned long long	sum;
	int					sign;
	int					i;

	sum = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		sum = sum * 10 + str[i++] - 48;
	return (sum);
}

static int	is_number(char *s)
{
	int					i;
	unsigned long long	nb;

	i = -1;
	if (s && (s[0] == '+' || s[0] == '-'))
		i++;
	while (s && s[++i])
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (0);
	}
	nb = ft_atoull(s);
	if (i > 19 || nb > LLONG_MAX)
		return (0);
	return (1);
}

void	ft_exit(t_mini *mini, t_cmd *cmd)
{
	char	*s;

	write(STDERR_FILENO, "exit\n", 6);
	s = ft_strdup(mini, "bash: exit: ");
	if (is_number(cmd->cmds[1]) && cmd->cmds[2])
	{
		s = ft_strjoin(mini, s, ARG_ERR);
		ft_putendl_fd(s, STDOUT_FILENO);
		free(s);
	}
	else
	{
		if (!is_number(cmd->cmds[1]))
		{
			s = ft_strjoin(mini, s, cmd->cmds[1]);
			s = ft_strjoin(mini, s, ": ");
			s = ft_strjoin(mini, s, NUM_ERR);
			ft_putendl_fd(s, STDOUT_FILENO);
		}
		free(s);
		ft_free_all(mini);
		exit(g_status);
	}
}
