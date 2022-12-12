/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:28:01 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/02 13:55:45 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minish.h"

int	ft_lstsize(t_var *var)
{
	int	i;

	if (!var)
		return (0);
	i = 0;
	while (var->next)
	{
		i++;
		var = var->next;
	}
	return (++i);
}
