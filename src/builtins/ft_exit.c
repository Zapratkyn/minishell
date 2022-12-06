/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 16:55:54 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/06 16:38:54 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minish.h"

void	ft_exit(t_mini *mini)
{
	ft_free_all(mini);
	write(STDERR_FILENO, "\nexit\n", 6);
	exit(g_status);
}
