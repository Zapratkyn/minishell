/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sortlst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:08:48 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/30 19:07:19 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
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
/*
#include <stdio.h>
int main (void)
{
	t_var	*tmp;
	t_var	*l1;
	t_var	*l2;
	t_var	*l3;
	t_var	*l4;
	t_var	*l5;

	l1 = ft_lstnew("hey");
	l2 = ft_lstnew("lol");
	l3 = ft_lstnew("pouet");
	l4 = ft_lstnew("aaa");
	l5 = ft_lstnew("bb");
	ft_lstadd_back(&l1, l2);
	ft_lstadd_back(&l1, l3);
	ft_lstadd_back(&l1, l4);
	ft_lstadd_back(&l1, l5);
	ft_sortlst(l1);
	while (l1)
	{
		printf("\n%s\n", l1->content);
		l1 = l1->next;
	}
}
*/