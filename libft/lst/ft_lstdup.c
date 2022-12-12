/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:15:28 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/12 16:06:08 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minish.h"

t_var	*ft_lstdup(t_mini *mini, t_var *var)
{
	t_var	*dup;
	t_var	*tmp;

	tmp = var;
	dup = ft_lstnew(mini, ft_strdup(mini, var->content));
	tmp = tmp->next;
	while (tmp)
	{
		ft_lstadd_back(&dup, ft_lstnew(mini, ft_strdup(mini, tmp->content)));
		tmp = tmp->next;
	}
	return (dup);
}
