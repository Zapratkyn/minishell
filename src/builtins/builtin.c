/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:54:58 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/23 13:44:57 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minish.h"

void	do_builtin(t_mini *mini, t_cmd *cmd, int builtin)
{
	if (builtin == ECHO)
		ft_echo(cmd);
	else if (builtin == CD)
		ft_cd(mini, cmd);
	//else if (builtin == PWD)
	//	cmd_pwd(cmd);
	//else if (builtin == EXPORT)
	//	cmd_export(cmd);
	//else if (builtin == UNSET)
	//	cmd_unset(cmd);
	//else if (builtin == ENV)
	//	cmd_env(cmd);
	//else if (builtin == EXIT)
	//	cmd_exit(cmd);
}

int	is_builtin(t_cmd *cmd)
{
	if (!cmd->cmd[0])
		ft_error(CMD_ERR);
	else if (!ft_strcmp("echo", cmd->cmd[0]))
		return (ECHO);
	else if (!ft_strcmp("cd", cmd->cmd[0]))
		return (CD);
	else if (!ft_strcmp("pwd", cmd->cmd[0]))
		return (PWD);
	else if (!ft_strcmp("export", cmd->cmd[0]))
		return (EXPORT);
	else if (!ft_strcmp("unset", cmd->cmd[0]))
		return (UNSET);
	else if (!ft_strcmp("env", cmd->cmd[0]))
		return (ENV);
	else if (!ft_strcmp("exit", cmd->cmd[0]))
		return (EXIT);
	return (0);
}
