/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:54:58 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/28 14:22:55 by gponcele         ###   ########.fr       */
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
	//else if (ft_strcmp(cmd->cmds[0], "cd"))
	//	ft_cd(mini, cmd);
	//else if (builtin == EXPORT)
	//	cmd_export(cmd);
	//else if (builtin == UNSET)
	//	cmd_unset(cmd);
	//else if (builtin == EXIT)
	//	cmd_exit(cmd);
}

int	is_builtin(t_cmd *cmd)
{
	if (!cmd->cmds[0])
		ft_error(CMD_ERR, 1);
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
