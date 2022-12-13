/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 16:55:54 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/13 16:41:04 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minish.h"

unsigned long long	ft_atoull(const char *str)
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

int	is_exit_number(char *s)
{
	int					i;
	unsigned long long	nb;

	i = -1;
	if (!s)
		return (0);
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
	ft_putendl_fd("exit", STDERR_FILENO);
	if (is_exit_number(cmd->cmds[1]) && cmd->cmds[2])
	{
		ft_error(mini, ARG_ERR, NO_EXIT);
		g_status = 1;
	}
	else
	{
		if (cmd->cmds[1] && !is_exit_number(cmd->cmds[1]))
		{
			ft_error(mini, NUM_ERR, NO_EXIT);
			g_status = 255;
			ft_free_all(mini);
			exit(g_status);
		}
		ft_free_all(mini);
		g_status = ft_atoull(cmd->cmds[1]);
		exit(g_status);
	}
}
