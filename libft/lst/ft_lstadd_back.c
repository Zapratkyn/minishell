/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 14:43:32 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/12 16:56:35 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minish.h"

void	ft_lstadd_back(t_var **var, t_var *new)
{
	if (!var || !new)
		return ;
	else if (!*var)
		*var = new;
	else
		ft_lstlast(*var)->next = new;
}
