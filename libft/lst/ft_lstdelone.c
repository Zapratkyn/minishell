/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:43:28 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/12 12:14:53 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minish.h"

void	ft_lstdelone(t_var **l_var, int i)
{
	t_var	*prev;
	t_var	*var;
	t_var	*next;

	(void)var;
	prev = ft_lstget(*l_var, i - 1);
	var = ft_lstget(*l_var, i);
	next = ft_lstget(*l_var, i + 1);
	if (prev && next)
		prev->next = next;
	else if (prev && !next)
		prev->next = NULL;
	else if (!prev && next)
		var = next;
	else
		var = NULL;
	(void) var;
}
