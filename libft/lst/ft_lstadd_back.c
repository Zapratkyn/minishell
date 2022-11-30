/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 14:43:32 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/30 18:16:31 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstadd_back(t_var **var, t_var *new)
{
	if (!var || !new)
		return ;
	else if (!*var)
		*var = new;
	else
		ft_lstlast(*var)->next = new;
}