/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:35:14 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/06 13:36:15 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

void	ft_put_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab && tab[++i])
		ft_putstr_fd(tab[i], STDOUT_FILENO);
}
