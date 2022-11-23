/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:21:10 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/22 16:04:16 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

void	redir(t_cmd *cmd)
{
	if (cmd->infile != STDIN_FILENO)
	{
		if (dup2(cmd->infile, STDIN_FILENO == -1))
			ft_error(DUP_ERROR);
		close(cmd->infile);
	}
	if (cmd->outfile != STDOUT_FILENO)
	{
		if (dup2(cmd->outfile, STDOUT_FILENO) == -1)
			ft_error(DUP_ERROR);
		close(cmd->outfile);
	}
	else if (cmd->next)
		if (dup2(cmd->next->infile, cmd->fd[WRITE]) == -1)
			ft_error(DUP_ERROR);
	close(cmd->fd[WRITE]);
	close(cmd->fd[READ]);
}

void	exec_child(t_mini *mini, t_cmd *cmd)
{
	redir(cmd);
	if (cmd->path)
		execve(cmd->path, cmd->cmd, mini->env);
}

void	execute(t_mini *mini)
{
	while (mini->cmd)
	{
		if (pipe(mini->cmd->fd) == -1)
			ft_error(PIPE_ERROR);
		mini->cmd->pid = fork();
		if (mini->cmd->pid == -1)
			ft_error(FORK_ERROR);
		else if (mini->cmd->pid == CHILD)
			exec_child(mini, mini->cmd);
		close(mini->cmd->fd[READ]);
		if (mini->cmd->next && mini->cmd->infile == STDIN_FILENO)
			mini->cmd->next->infile = mini->cmd->fd[READ];
		else
			close(mini->cmd->fd[READ]);
		if (mini->cmd->infile > 2)
			close(mini->cmd->infile);
		if (mini->cmd->outfile > 2)
			close(mini->cmd->outfile);
		mini->cmd = mini->cmd->next;
	}
}