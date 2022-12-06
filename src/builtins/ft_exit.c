/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 16:55:54 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/06 12:38:40 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minish.h"

void	ft_free_all(t_mini *mini)
{
	if (mini->prompt)
		free(mini->prompt);
	ft_lstclear(&mini->var);
	free(mini->var);
	ft_free_cmd(mini->cmd);
}

void	ft_exit(t_mini *mini)
{
	ft_free_all(mini);
	write(STDERR_FILENO, "\nexit\n", 6);
	exit(g_status);
}
