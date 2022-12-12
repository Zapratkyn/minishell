/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:15:28 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/02 13:55:45 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minish.h"

t_var	*ft_lstdup(t_mini *mini, t_var *var)
{
	t_var	*dup;
	t_var	*tmp;

	tmp = var;
	dup = ft_lstnew(mini, var->content);
	tmp = tmp->next;
	while (tmp)
	{
		ft_lstadd_back(&dup, ft_lstnew(mini, tmp->content));
		tmp = tmp->next;
	}
	return (dup);
}
