/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 16:55:56 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/14 13:18:05 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minish.h"

static int	check_err2(t_mini *mini, char *s, int i)
{
	if (ft_strcmp(s, "=") && ft_strchr(s, '='))
	{
		ft_error(mini, UNSET_ID_ERR, NO_EXIT);
		g_status = 1;
		return (0);
	}
	while (s && s[i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
		{
			g_status = 1;
			ft_error(mini, UNSET_ID_ERR, NO_EXIT);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	check_err(t_mini *mini, char *s, int i)
{
	if (!ft_strcmp(s, "PWD") || !ft_strcmp(s, "OLDPWD")
		|| !ft_strcmp(s, "HOME"))
	{
		g_status = 1;
		ft_error(mini, UNSET_VAR_ERR, NO_EXIT);
		return (0);
	}
	if (s && (s[0] == '=' || !s[0]))
	{
		g_status = 1;
		ft_error(mini, UNSET_NAME_ERR, NO_EXIT);
		return (0);
	}
	return (check_err2(mini, s, i));
}

void	ft_unset(t_mini *mini, t_cmd *cmd, int i, char *s)
{
	t_var	*var;

	if (!cmd->cmds[1] && !check_option(mini, cmd, "unset"))
		return ;
	while (cmd->cmds[++i])
	{
		if (!check_err(mini, cmd->cmds[i], 0))
			continue ;
		g_status = 0;
		var = mini->var;
		while (var)
		{
			s = ft_rev_strchr(mini, var->content, '=');
			if ((!s && !ft_strcmp(var->content, cmd->cmds[i]))
				|| !ft_strcmp(s, cmd->cmds[i]))
			{
				ft_lstdelone(&mini->var, ft_lst_index(&mini->var, var));
				free(s);
				break ;
			}
			if (s)
				free(s);
			var = var->next;
		}
	}
}
