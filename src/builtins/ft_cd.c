/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:40:09 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/13 13:05:21 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minish.h"

void	update_oldpwd(t_mini *mini, char *path)
{
	t_var	*var;
	char	*o_pwd;

	o_pwd = "OLDPWD=";
	var = mini->var;
	while (var)
	{
		if (!ft_strncmp(var->content, o_pwd, ft_strlen(o_pwd)))
		{
			free(var->content);
			var->content = ft_strjoin(mini, ft_strdup(mini, o_pwd), path);
			break ;
		}
		var = var->next;
	}
}

void	update_pwd(t_mini *mini)
{
	t_var	*var;
	char	*tmp;
	char	*pwd;

	pwd = ft_strdup(mini, "PWD=");
	var = mini->var;
	tmp = NULL;
	while (var)
	{
		if (!ft_strncmp(var->content, pwd, ft_strlen(pwd)))
		{
			tmp = getcwd(tmp, 0);
			if (!tmp)
				ft_error(mini, PWD_ERR, EXIT);
			free(var->content);
			var->content = ft_strjoin(mini, pwd, tmp);
			free(tmp);
			break ;
		}
		var = var->next;
	}
}

char	*find_path(t_mini *mini, t_cmd *cmd, char *s)
{
	char	*path;

	if (!cmd->cmds[1] || !ft_strcmp(cmd->cmds[1], "~")
		|| !ft_strcmp(cmd->cmds[1], "--"))
		return (ft_strdup(mini, mini_getenv(mini, "HOME")));
	if (!ft_strncmp("/", cmd->cmds[1], 1))
		return (ft_strdup(mini, cmd->cmds[1]));
	if (!ft_strcmp("-", cmd->cmds[1]))
		return (ft_strdup(mini, mini_getenv(mini, "OLDPWD")));
	if (!ft_strncmp(cmd->cmds[1], "~/", 2))
	{
		path = ft_strdup(mini, mini_getenv(mini, "HOME"));
		path = ft_strjoin(mini, path, "/");
		path = ft_strjoin(mini, path, &cmd->cmds[1][2]);
	}
	else
	{
		s = getcwd(s, 0);
		if (!s)
			ft_error(mini, PWD_ERR, EXIT);
		path = ft_insert(mini, s, '/', cmd->cmds[1]);
		free(s);
	}
	return (path);
}

void	ft_cd(t_mini *mini, t_cmd *cmd)
{
	char	*path;
	char	*tmp;
	char	*s;

	if (!check_option(mini, cmd, "cd"))
		return ;
	tmp = mini_getenv(mini, "PWD");
	s = NULL;
	path = find_path(mini, cmd, s);
	if (chdir(path) == -1)
	{
		free(path);
		g_status = 1;
		ft_error(mini, DIR_ERR, NO_EXIT);
	}
	else
	{
		update_oldpwd(mini, tmp);
		update_pwd(mini);
		free(path);
	}
	mini->prompt = get_prompt(mini, mini->prompt);
}
