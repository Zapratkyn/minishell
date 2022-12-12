/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:41:03 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/12 12:28:23 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minish.h"

void	ft_lstclear(t_var *var)
{
	if (var->next)
		ft_lstclear(var->next);
	if (var->content)
	{
		free (var->content);
		var->content = NULL;
	}
	if (var)
	{
		free (var);
		var = NULL;
	}
}
