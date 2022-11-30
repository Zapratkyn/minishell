/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 16:54:36 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/30 13:09:59 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minish.h"

char	*export_strchr(char *str, char c)
{
	int	i;

	i = -1;
	while (str && str[++i])
		if (str[i] == c && str[i + 1])
			return (ft_substr(str, i + 1, ft_strlen(&str[i + 1])));
	return (NULL);
}

void	modif_var(t_mini *mini, char *name_var, char *s)
{
	t_var	*var;

	var = mini->var;
	while (var)
	{
		if (!ft_strncmp(var->content, name_var, ft_strlen(name_var)))
		{
			free(var->content);
			var->content = ft_insert(name_var, '=', s);
		}
		var = var->next;
	}
}

void	do_export(t_mini *mini, int index, char *s1, char *s2)
{
	if (!s1 && !is_env(mini, mini->cmd->cmds[index]))
	{
		ft_lstadd_back(&mini->var, ft_lstnew(mini->cmd->cmds[index]));
		modif_var(mini, mini->cmd->cmds[index], "");
	}
	if (s1 && s2 && !is_env(mini, mini->cmd->cmds[index]))
		ft_lstadd_back(&mini->var, ft_lstnew(mini->cmd->cmds[index]));
	else if (s1 && s2 && is_env(mini, mini->cmd->cmds[index]))
		modif_var(mini, s1, s2);
	else if (s1 && !s2 && is_env(mini, mini->cmd->cmds[index]))
		modif_var(mini, s1, "");
	else if (s1 && !s2 && !is_env(mini, mini->cmd->cmds[index]))
		ft_lstadd_back(&mini->var, ft_lstnew(ft_strdup(mini->cmd->cmds[index])));
	if (s1)
		free(s1);
	if (s2)
		free(s2);
}

static void	display_exp(t_mini *mini)
{
	t_var	*var;

	var = mini->var;
	while (var)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_n_putstr(var->content, ft_find_index(var->content, '=') + 1);
		write(STDOUT_FILENO, "\"", 1);
		ft_putstr_fd(&var->content[ft_find_index(var->content, '=') + 1],
				STDOUT_FILENO);
		write(STDOUT_FILENO, "\"", 1);
		write(STDOUT_FILENO, "\n", 1);
		var = var->next;
	}
}

void	ft_export(t_mini *mini, t_cmd *cmd)
{
	char	*s1;
	char	*s2;
	int		i;

	if (!cmd->cmds[1])
		display_exp(mini);
	else
	{
		i = 0;
		while (cmd->cmds[++i])
		{
			remove_quotes(cmd, i, cmd->cmds[i]);
			s1 = ft_rev_strchr(cmd->cmds[i], '=');
			s2 = export_strchr(cmd->cmds[i], '=');
			do_export(mini, i, s1, s2);
		}
	}
}