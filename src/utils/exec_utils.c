/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:13:44 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/22 12:45:23 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minish.h"

void	pipe_and_fork(t_mini *mini, t_cmd *cmd)
{
	if (pipe(cmd->fd) == -1)
		ft_error(mini, PIPE_ERR, EXIT);
	if (n_of_cmd(cmd) == 1 && par_builtin(cmd))
		do_builtin(mini, cmd);
	cmd->pid = fork();
	if (cmd->pid == -1)
		ft_error(mini, FORK_ERR, EXIT);
	else if (cmd->pid == CHILD_PROC)
		exec_child(mini, cmd);
	wait(&g_status);
	if (WIFEXITED(g_status))
		g_status = WEXITSTATUS(g_status);
	else if (WIFSIGNALED(g_status))
	{
		g_status = WTERMSIG(g_status);
		if (g_status != 1)
			g_status -= 1;
	}
}

int	check_cmd(t_mini *mini, t_cmd *cmd)
{
	if (cmd->infile < 0 || cmd->outfile < 0)
	{
		if (cmd->infile == -1)
			g_status = 1;
		return (0);
	}
	if (!ch_builtin(cmd) && !par_builtin(cmd)
		&& !cmd->path)
		return (0);
	if (ch_builtin(cmd) && !check_builtin(mini, cmd))
	{
		g_status = 1;
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

void	mini_new_line(int sig)
{
	(void)sig;
	g_status = 1;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
}
