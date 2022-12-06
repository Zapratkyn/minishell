/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 16:55:54 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/06 17:24:03 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minish.h"

void	ft_exit(t_mini *mini)
{
	int	is_cmd_exit;

	is_cmd_exit = 0;
	if (mini->cmd && mini->cmd->cmds && !ft_strcmp(mini->cmd->cmds[0], "exit"))
		is_cmd_exit = 1;
	ft_free_all(mini);
	if (is_cmd_exit)
		write(STDERR_FILENO, "exit\n", 6);
	else
		write(STDERR_FILENO, "\nexit\n", 6);
	exit(g_status);
}
