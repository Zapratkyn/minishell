/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:54:58 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/12 16:29:10 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minish.h"

int	check_builtin(t_mini *mini, t_cmd *cmd)
{
	if (!ft_strcmp("pwd", cmd->cmds[0]))
		return (check_option(mini, cmd, "pwd"));
	else if (!ft_strcmp("env", cmd->cmds[0]))
		return (check_option(mini, cmd, "env"));
	return (1);
}

void	do_builtin(t_mini *mini, t_cmd *cmd)
{
	char	*s;

	s = NULL;
	if (!ft_strcmp(cmd->cmds[0], "echo"))
		ft_echo(mini, cmd);
	else if (!ft_strcmp(cmd->cmds[0], "env"))
		ft_env(mini);
	else if (!ft_strcmp(cmd->cmds[0], "pwd"))
		ft_pwd(mini);
	else if (!ft_strcmp(cmd->cmds[0], "cd"))
		ft_cd(mini, cmd);
	else if (!ft_strcmp(cmd->cmds[0], "exit"))
		ft_exit(mini, cmd, s);
	else if (!ft_strcmp(cmd->cmds[0], "export"))
		ft_export(mini, cmd);
	else if (!ft_strcmp(cmd->cmds[0], "unset"))
		ft_unset(mini, cmd, 0);
}

int	par_builtin(t_mini *mini, t_cmd *cmd)
{
	if (!cmd->cmds[0])
		ft_error(mini, CMD_ERR, EXIT);
	else if (!ft_strcmp("export", cmd->cmds[0]) && cmd->cmds[1])
		return (1);
	else if (!ft_strcmp("exit", cmd->cmds[0]))
		return (1);
	else if (!ft_strcmp("cd", cmd->cmds[0]))
		return (1);
	else if (!ft_strcmp("unset", cmd->cmds[0]))
		return (1);
	return (0);
}

int	ch_builtin(t_mini *mini, t_cmd *cmd)
{
	if (!cmd->cmds[0])
		ft_error(mini, CMD_ERR, EXIT);
	else if (!ft_strcmp("echo", cmd->cmds[0]))
		return (1);
	else if (!ft_strcmp("pwd", cmd->cmds[0]))
		return (1);
	else if (!ft_strcmp("env", cmd->cmds[0]))
		return (1);
	else if (!ft_strcmp("export", cmd->cmds[0]) && !cmd->cmds[1])
		return (1);
	return (0);
}
