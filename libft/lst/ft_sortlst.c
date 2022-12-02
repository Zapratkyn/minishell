/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sortlst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:08:48 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/02 13:55:45 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minish.h"
#include <stdio.h>

t_var	*ft_sortlst(t_var *var)
{
	char	*swap;
	t_var	*tmp;

	tmp = var;
	while (var->next)
	{
		if (ft_strcmp(var->content, var->next->content) > 0)
		{
			swap = var->content;
			var->content = var->next->content;
			var->next->content = swap;
			var = tmp;
		}
		else
			var = var->next;
	}
	var = tmp;
	return (var);
}
