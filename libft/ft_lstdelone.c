/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:43:28 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/30 15:19:34 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_var **l_var, t_var *var)
{
	if (!l_var || !*l_var || !var)
		return ;
	if (!var->prev)
		*l_var = var->next;
	else if (!var->next)
		var->prev->next = NULL;
	else
		var->prev->next = var->next;
	if (var->content)
		free(var->content);
	var->next = NULL;
	var->prev = NULL;
	if (var)
		free(var);
}
