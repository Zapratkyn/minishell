/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 16:54:36 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/13 22:03:51 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minish.h"

static char	*export_strchr(t_mini *mini, char *str, char c)
{
	int	i;

	i = -1;
	while (str && str[++i])
		if (str[i] == c && str[i + 1])
			return (ft_substr(mini, str, i + 1, ft_strlen(&str[i + 1])));
	return (NULL);
}

void	do_export(t_mini *mini, t_cmd *cmd, int i)
{
	if (!mini->tempstr && !is_env(mini, cmd->cmds[i]))
		ft_lstadd_back(&mini->var, ft_lstnew(mini, ft_strdup(mini,
					cmd->cmds[i])));
	if (mini->tempstr && mini->tempstr2 && !is_env(mini, cmd->cmds[i]))
		ft_lstadd_back(&mini->var, ft_lstnew(mini, ft_strdup(mini,
					cmd->cmds[i])));
	else if (mini->tempstr && mini->tempstr2 && is_env(mini, cmd->cmds[i]))
		modif_var(mini, mini->tempstr, mini->tempstr2);
	else if (mini->tempstr && !mini->tempstr2 && is_env(mini, cmd->cmds[i]))
		modif_var(mini, mini->tempstr, "");
	else if (mini->tempstr && !mini->tempstr2 && !is_env(mini, cmd->cmds[i]))
		ft_lstadd_back(&mini->var, ft_lstnew(mini,
				ft_strdup(mini, cmd->cmds[i])));
	if (mini->tempstr)
	{
		free(mini->tempstr);
		mini->tempstr = NULL;
	}
	if (mini->tempstr2)
	{
		free(mini->tempstr2);
		mini->tempstr2 = NULL;
	}
}

static void	display_exp(t_mini *mini)
{
	t_var	*var;
	t_var	*tmp;

	var = ft_lstdup(mini, mini->var);
	ft_sortlst(var);
	tmp = var;
	while (var)
	{
		ft_n_putstr(var->content, ft_find_index(var->content, '=') + 1);
		if (ft_strchr(var->content, '='))
			write(STDOUT_FILENO, "\"", 1);
		ft_putstr_fd(&var->content[ft_find_index(var->content, '=') + 1],
			STDOUT_FILENO);
		if (ft_strchr(var->content, '='))
			write(STDOUT_FILENO, "\"", 1);
		write(STDOUT_FILENO, "\n", 1);
		var = var->next;
	}
	ft_lstclear(tmp);
}

static int	check_export(t_mini *mini, char *s)
{
	int		i;

	if (s && (s[0] == '=' || !s[0] || ft_isdigit(s[0])))
	{
		g_status = 1;
		ft_error(mini, EXPORT_ERR, NO_EXIT);
		return (0);
	}
	i = 0;
	while (s && s[i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
		{
			g_status = 1;
			ft_error(mini, EXPORT_ERR, NO_EXIT);
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_export(t_mini *mini, t_cmd *cmd)
{
	int		i;

	if (!cmd->cmds[1])
		display_exp(mini);
	if (!check_option(mini, cmd, "export"))
		return ;
	else
	{
		i = 0;
		while (cmd->cmds[++i])
		{
			if (!check_export(mini, cmd->cmds[i]))
				continue ;
			g_status = 0;
			mini->tempstr = ft_rev_strchr(mini, cmd->cmds[i], '=');
			mini->tempstr2 = export_strchr(mini, cmd->cmds[i], '=');
			do_export(mini, cmd, i);
		}
	}
}
