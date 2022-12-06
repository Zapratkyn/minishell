/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 16:55:54 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/06 17:57:13 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minish.h"

void	ft_exit(t_mini *mini, t_cmd *cmd)
{
	int	is_cmd_exit;

	is_cmd_exit = 0;
	if (ft_tablen(cmd->cmds) <= 2)
	{
		ft_free_all(mini);
		write(STDERR_FILENO, "exit\n", 6);
		exit(g_status);
	}
	else
		ft_putendl_fd(EXIT_ERR, STDOUT_FILENO);
}
