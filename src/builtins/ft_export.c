/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 16:54:36 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/13 12:11:27 by ademurge         ###   ########.fr       */
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

static void	do_export(t_mini *mini, int index, char *s1, char *s2)
{
	if (!s1 && !is_env(mini, mini->cmd->cmds[index]))
		ft_lstadd_back(&mini->var, ft_lstnew(mini, ft_strdup(mini,
					mini->cmd->cmds[index])));
	if (s1 && s2 && !is_env(mini, mini->cmd->cmds[index]))
		ft_lstadd_back(&mini->var, ft_lstnew(mini, ft_strdup(mini,
					mini->cmd->cmds[index])));
	else if (s1 && s2 && is_env(mini, mini->cmd->cmds[index]))
		modif_var(mini, s1, s2);
	else if (s1 && !s2 && is_env(mini, mini->cmd->cmds[index]))
		modif_var(mini, s1, "");
	else if (s1 && !s2 && !is_env(mini, mini->cmd->cmds[index]))
		ft_lstadd_back(&mini->var, ft_lstnew(mini,
				ft_strdup(mini, mini->cmd->cmds[index])));
	if (s1)
		free(s1);
	if (s2)
		free(s2);
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
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
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
	ft_lstclear(&tmp);
}

static int	check_export(t_mini *mini, char *s)
{
	int		i;

	if (s && (s[0] == '=' || !s[0]))
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
	char	*s1;
	char	*s2;
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
			s1 = ft_rev_strchr(mini, cmd->cmds[i], '=');
			s2 = export_strchr(mini, cmd->cmds[i], '=');
			do_export(mini, i, s1, s2);
		}
	}
}
