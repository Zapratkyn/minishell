/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:43:28 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/22 12:25:02 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minish.h"

void	ft_lstdelone(t_var **l_var, int i)
{
	t_var	*prev;
	t_var	*var;
	t_var	*next;

	var = ft_lstget(*l_var, i);
	next = ft_lstget(*l_var, i + 1);
	prev = ft_lstget(*l_var, i - 1);
	free(var->content);
	free(var);
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
