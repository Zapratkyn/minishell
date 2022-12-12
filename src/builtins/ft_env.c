/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 12:53:23 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/12 11:17:55 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minish.h"

void	ft_env(t_mini *mini, t_cmd *cmd)
{
	t_var	*var;

	(void) cmd;
	var = mini->var;
	while (var)
	{
		ft_putstr_fd(var->content, STDOUT_FILENO);
		write(STDOUT_FILENO, "\n", 1);
		var = var->next;
	}
}
