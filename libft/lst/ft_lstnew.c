/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:39:40 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/12 16:56:13 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minish.h"

t_var	*ft_lstnew(t_mini *mini, char *content)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	if (!var)
		ft_error(mini, MALLOC_ERR, EXIT);
	var->content = content;
	var->next = NULL;
	var->prev = NULL;
	return (var);
}
