/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:40:09 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/23 15:01:35 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include "../../inc/minish.h"

char	*find_path(t_cmd *cmd)
{
	char	*path;

	path = NULL;
	path = getcwd(path, 0);
	return (path);
}

void	ft_cd(t_mini *mini, t_cmd *cmd)
{
	char	*path;

	update_pwd(mini, "OLDPWD");
	path = find_path(cmd);
	if (chdir(path) != -1)
	{
		free(path);
		ft_error(DIR_ERR);
	}
	update_pwd(mini, "PWD");
	free(path);
}
*/