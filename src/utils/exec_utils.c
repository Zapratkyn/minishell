/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:13:44 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/29 16:39:10 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minish.h"

void	pipe_and_fork(t_mini *mini, t_cmd *cmd)
{
	if (pipe(cmd->fd) == -1)
	ft_error(PIPE_ERR, EXIT);
	cmd->pid = fork();
	if (cmd->pid == -1)
		ft_error(FORK_ERR, EXIT);
	else if (cmd->pid == CHILD_PROC)
		exec_child(mini, cmd);
	waitpid(cmd->pid, NULL, 0);
}

int	check_cmd(t_cmd *cmd)
{
	if (cmd->infile == -1 || cmd->outfile == -1)
	{
		cmd = cmd->next;
		return (0);
	}
	if (!ch_builtin(cmd) && !par_builtin(cmd) && !cmd->path)
	{
		cmd = cmd->next;
		return (0);
	}
	return (1);
}

int	n_of_cmd(t_cmd *cmd)
{
	int		n;
	t_cmd	*tmp;

	n = 0;
	tmp = cmd;
	while (tmp)
	{
		n++;
		tmp = tmp->next;
	}
	return (n);
}
