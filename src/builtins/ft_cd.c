/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:40:09 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/23 16:20:25 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minish.h"

char	*find_path(t_mini *mini, t_cmd *cmd)
{
	char	*path;
	char	*tmp;

	path = NULL;
	if (!ft_strcmp("-", cmd->cmd[1]))
		path = ft_strdup(mini_getenv(mini, "OLDPWD"));
	else
	{
		path = getcwd(path, 0);
		ft_strjoin(path, "/");
		ft_strjoin(path, cmd->cmd[1]);
	}
	return (path);
}

void	ft_cd(t_mini *mini, t_cmd *cmd)
{
	char	*path;

	update_pwd(mini, "OLDPWD");
	path = find_path(mini, cmd);
	if (chdir(path) != -1)
	{
		free(path);
		ft_error(DIR_ERR);
	}
	update_pwd(mini, "PWD");
	free(path);
}
