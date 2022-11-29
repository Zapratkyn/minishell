/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:54:58 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/29 13:13:19 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minish.h"

void	do_builtin(t_mini *mini, t_cmd *cmd)
{
	(void) mini;
	if (!ft_strcmp(cmd->cmds[0], "echo"))
		ft_echo(cmd);
	else if (!ft_strcmp(cmd->cmds[0], "env"))
		ft_env(mini, cmd);
	else if (!ft_strcmp(cmd->cmds[0], "pwd"))
		ft_pwd(cmd);
	else if (!ft_strcmp(cmd->cmds[0], "exit"))
		ft_exit(mini);
}

int	is_builtin(t_cmd *cmd)
{
	if (!cmd->cmds[0])
		ft_error(CMD_ERR, EXIT);
	else if (!ft_strcmp("echo", cmd->cmds[0]))
		return (1);
	else if (!ft_strcmp("cd", cmd->cmds[0]))
		return (1);
	else if (!ft_strcmp("pwd", cmd->cmds[0]))
		return (1);
	else if (!ft_strcmp("export", cmd->cmds[0]))
		return (1);
	else if (!ft_strcmp("unset", cmd->cmds[0]))
		return (1);
	else if (!ft_strcmp("env", cmd->cmds[0]))
		return (1);
	else if (!ft_strcmp("exit", cmd->cmds[0]))
		return (1);
	return (0);
}
