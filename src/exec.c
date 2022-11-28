/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:21:10 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/28 16:55:22 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

void	check_cmd(t_cmd *cmd)
{
	(void) cmd;
	// code
}

void	redir(t_cmd *cmd)
{
	if (cmd->infile != STDIN_FILENO)
	{
		if (dup2(cmd->infile, STDIN_FILENO) == -1)
			ft_error(DUP_ERR, EXIT);
		close(cmd->infile);
		close(cmd->fd[READ]);
	}
	if (cmd->outfile != STDOUT_FILENO)
	{
		if (dup2(cmd->outfile, STDOUT_FILENO) == -1)
			ft_error(DUP_ERR, EXIT);
		close(cmd->outfile);
	}
}

void	exec_child(t_mini *mini, t_cmd *cmd)
{
	redir(cmd);
	if (is_builtin(cmd))
		do_builtin(mini, cmd);
	else if (cmd->path)
		execve(cmd->path, cmd->cmds, ft_lst_to_str(mini->var));
	exit(EXIT_SUCCESS);
}

void	execute(t_mini *mini)
{
	while (mini->cmd)
	{
		if (pipe(mini->cmd->fd) == -1)
			ft_error(PIPE_ERR, EXIT);
		mini->cmd->pid = fork();
		if (mini->cmd->pid == -1)
			ft_error(FORK_ERR, EXIT);
		else if (mini->cmd->pid == CHILD_PROC)
			exec_child(mini, mini->cmd);
		waitpid(mini->cmd->pid, NULL, 0);
//		close(mini->cmd->infile);
//		close(mini->cmd->outfile);
		close(mini->cmd->fd[READ]);
		close(mini->cmd->fd[WRITE]);
		mini->cmd = mini->cmd->next;
	}
}
