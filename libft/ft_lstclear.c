/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:41:03 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/30 14:51:01 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_var **var)
{
	t_var	*tmp;

	while (var && *var)
	{
		tmp = (*var)->next;
		ft_lstdelone(var, *var);
		*var = tmp;
	}
}
