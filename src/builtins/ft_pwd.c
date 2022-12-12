/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 10:52:09 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/12 10:51:52 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minish.h"

void	ft_pwd(t_mini *mini, t_cmd *cmd)
{
	char	*pwd;

	if (cmd->cmds[1][0] == '-' && cmd->cmds[1][1])
		return (ft_error(mini, "minishell: pwd: invalid option", NO_EXIT));
	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (!pwd)
		ft_error(mini, PWD_ERR, EXIT);
	ft_putstr_fd(pwd, STDOUT_FILENO);
	write(STDOUT_FILENO, "\n", 1);
	free(pwd);
}
