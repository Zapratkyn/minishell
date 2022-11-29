/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 16:54:36 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/29 16:58:36 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minish.h"

void	ft_export(t_mini *mini, t_cmd *cmd)
{
	(void) mini;
	printf("%s\n", cmd->cmds[1]);
	if (!cmd->cmds[1])
		ft_env(mini, cmd);
}
