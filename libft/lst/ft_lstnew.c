/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:39:40 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/02 13:55:45 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minish.h"

t_var	*ft_lstnew(t_mini *mini, char *content)
{
	t_var	*var;

	var = (t_var *)malloc(sizeof(t_var));
	if (!var)
		ft_error(mini, MALLOC_ERR, EXIT);
	var->content = content;
	var->next = NULL;
	var->prev = NULL;
	return (var);
}
