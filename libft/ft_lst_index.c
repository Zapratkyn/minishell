/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_index.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:30:53 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/30 15:49:22 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lst_index(t_var **l_var, t_var *var)
{
	t_var	*tmp;
	int		i;

	tmp = *l_var;
	i = 0;
	while (tmp)
	{
		if (!ft_strcmp(tmp->content, var->content))
			return (i);
		i++;
		tmp = tmp->next;
	}
	return (-1);
}
