/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 10:52:09 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/12 13:02:41 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minish.h"

void	ft_pwd(t_mini *mini)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (!pwd)
		ft_error(mini, PWD_ERR, EXIT);
	ft_putstr_fd(pwd, STDOUT_FILENO);
	write(STDOUT_FILENO, "\n", 1);
	free(pwd);
}
