/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:40:09 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/25 15:10:49 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minish.h"

void	update_pwd(t_mini *mini, char *type)
{
	t_var	*var;
	char	*tmp;

	var = mini->var;
	tmp = NULL;
	while (var)
	{
		if (!ft_strncmp(var->content, type, ft_strlen(type)))
		{
			tmp = getcwd(tmp, 0);
			if (!tmp)
				ft_error(PWD_ERR);
			free(var->content);
			var->content = ft_strjoin(type, tmp);
			free(tmp);
		}
		var = var->next;
	}
}

char	*find_path(t_mini *mini, t_cmd *cmd)
{
	char	*path;
	char	*tmp;

	tmp = NULL;
	if (!ft_strcmp("-", cmd->cmds[1]))
		path = ft_strdup(mini_getenv(mini, "OLDPWD"));
	else
	{
		tmp = getcwd(tmp, 0);
		if (!tmp)
			ft_error(PWD_ERR);
		path = ft_insert(tmp, '/', cmd->cmds[0]);
		free(tmp);
	}
	return (path);
}

void	ft_cd(t_mini *mini, t_cmd *cmd)
{
	char	*path;

	update_pwd(mini, "OLDPWD=");
	path = find_path(mini, cmd);
	if (chdir(path) == -1)
	{
		free(path);
		ft_error(DIR_ERR);
	}
	update_pwd(mini, "PWD");
	free(path);
}
