/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:39:40 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/30 18:16:49 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_var	*ft_lstnew(char *content)
{
	t_var	*var;

	var = (t_var *)malloc(sizeof(t_var));
	if (!var)
		return (NULL);
	var->content = content;
	var->next = NULL;
	var->prev = NULL;
	return (var);
}
