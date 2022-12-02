/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 16:55:56 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/02 13:34:35 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minish.h"

int	check_err(t_mini *mini, t_cmd *cmd, int index)
{
	char	*tmp;

	if (ft_strchr(cmd->cmds[index], '='))
	{
		tmp = ft_strdup(mini, "unset: ");
		tmp = ft_strjoin(mini, tmp, cmd->cmds[index]);
		tmp = ft_strjoin(mini, tmp, ": invalid parameter name");
		ft_error(mini, tmp, NO_EXIT);
		free(tmp);
		return (0);
	}
	return (1);
}

void	ft_unset(t_mini *mini, t_cmd *cmd)
{
	t_var	*var;
	char	*tmp;
	int		i;

	if (!cmd->cmds[1])
		return ;
	i = 0;
	while (cmd->cmds[++i])
	{
		if (!check_err(mini, cmd, i))
			continue ;
		var = mini->var;
		while (var)
		{
			tmp = ft_rev_strchr(mini, var->content, '=');
			if (!ft_strcmp(tmp, cmd->cmds[i]))
			{
				ft_lstdelone(&mini->var, ft_lst_index(&mini->var, var));
				free(tmp);
				break ;
			}
			free(tmp);
			var = var->next;
		}
	}
}
