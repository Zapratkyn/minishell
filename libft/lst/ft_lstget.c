/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstget.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:05:01 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/02 13:55:45 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minish.h"

t_var	*ft_lstget(t_var *var, int index)
{
	int	i;

	i = 0;
	while (var && i < index)
	{
		i++;
		var = var->next;
	}
	return (var);
}
