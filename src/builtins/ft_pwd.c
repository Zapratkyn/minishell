/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 10:52:09 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/25 17:36:28 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minish.h"

void	ft_pwd(t_cmd *cmd)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (!pwd)
		ft_error(PWD_ERR, EXIT);
	ft_putstr_fd(pwd, cmd->outfile);
	write(cmd->outfile, "\n", 1);
	free(pwd);
}