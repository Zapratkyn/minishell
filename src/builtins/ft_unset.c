/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 16:55:56 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/30 13:45:03 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minish.h"

void	ft_unset(t_mini *mini, t_cmd *cmd)
{
	t_var	*var;
	char	*tmp;
	int		i;

	if (!cmd->cmds[1])
		return ;
	else
	{
		i = -1;
		while (cmd->cmds[++i])
		{
			if (ft_strchr(cmd->cmds[i], '='))
			{
				ft_error("unset error", NO_EXIT);
				continue;
			}
			var = mini->var;
			while (var)
			{
				tmp = ft_rev_strchr(var->content, '=');
				if (!ft_strncmp(tmp, cmd->cmds[i], ft_strlen(tmp)))
					ft_lstdelone(var);
				free(tmp);
				var = var->next;
			}
		}
	}
}
