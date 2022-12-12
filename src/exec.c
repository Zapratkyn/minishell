/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:21:10 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/12 10:45:56 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

void	redir(t_mini *mini, t_cmd *cmd)
{
	if (cmd->infile != STDIN_FILENO)
	{
		if (dup2(cmd->infile, STDIN_FILENO) == -1)
			ft_error(mini, DUP_ERR, EXIT);
		close(cmd->infile);
	}
	if (cmd->outfile != STDOUT_FILENO)
	{
		if (dup2(cmd->outfile, STDOUT_FILENO) == -1)
			ft_error(mini, DUP_ERR, EXIT);
		close(cmd->outfile);
	}
	else if (cmd->next)
	{
		if (dup2(cmd->fd[WRITE], STDOUT_FILENO) == -1)
			ft_error(mini, DUP_ERR, EXIT);
	}
	close(cmd->fd[WRITE]);
	close(cmd->fd[READ]);
}

void	close_exec(t_cmd *cmd)
{
	close(cmd->fd[WRITE]);
	if (cmd->next && !cmd->next->infile)
		cmd->next->infile = cmd->fd[READ];
	else
		close(cmd->fd[READ]);
	if (cmd->infile > 2)
		close(cmd->infile);
	if (cmd->outfile > 2)
		close(cmd->outfile);
}

void	exec_child(t_mini *mini, t_cmd *cmd)
{
	redir(mini, cmd);
	if (ch_builtin(mini, cmd))
		do_builtin(mini, cmd);
	else if (cmd->path && !par_builtin(mini, cmd))
		execve(cmd->path, cmd->cmds, ft_lst_to_str(mini, mini->var));
	ft_free_all(mini);
	exit(g_status);
}

void	execute(t_mini *mini)
{
	t_cmd	*cmd;

	cmd = mini->cmd;
	while (cmd)
	{
		if (!check_cmd(mini, cmd))
		{
			cmd = cmd->next;
			continue ;
		}
		g_status = 0;
		if (cmd->path && !access(cmd->path, X_OK))
			g_status = 1;
		pipe_and_fork(mini, cmd);
		close_exec(cmd);
		cmd = cmd->next;
	}
}
