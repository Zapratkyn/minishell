/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:41:03 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/24 15:42:58 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst)
{
	t_list	*tmp;

	while (lst && *lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone(*lst);
		*lst = tmp;
	}
}
