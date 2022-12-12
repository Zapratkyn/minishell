/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 11:05:17 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/12 12:00:23 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minish.h"

char	*ft_rev_strchr(t_mini *mini, char *str, char c)
{
	int	i;

	i = -1;
	while (str && str[++i])
		if (str[i] == c)
			return (ft_substr(mini, str, 0, i));
	return (NULL);
}

int	is_env(t_mini *mini, char *s)
{
	t_var	*var;
	int		i;

	var = mini->var;
	while (var)
	{
		i = -1;
		while (var->content[++i])
			if (var->content[i] == '=')
				break ;
		if (!ft_strncmp(var->content, s, i))
			return (1);
		var = var->next;
	}
	return (0);
}

int	check_option(t_mini *mini, t_cmd *cmd, char *s)
{
	char	*err;

	if (cmd->cmds[1] && cmd->cmds[1][0] == '-' && cmd->cmds[1][1])
	{
		g_status = 1;
		err = ft_strdup(mini, "minishell: ");
		err = ft_strjoin(mini, err, s);
		err = ft_strjoin(mini, err, ": invalid option");
		ft_error(mini, err, NO_EXIT);
		free(err);
		return (0);
	}
	return (1);
}
