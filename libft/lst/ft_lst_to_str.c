/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_to_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:26:10 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/06 12:15:48 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minish.h"

char	**ft_lst_to_str(t_mini *mini, t_var *var)
{
	int		i;
	int		size;
	char	**tab;

	size = ft_lstsize(var);
	tab = malloc(sizeof(char *) * (size + 1));
	if (!tab)
		ft_error(mini, MALLOC_ERR, EXIT);
	i = -1;
	while (++i < size)
	{
		tab[i] = ft_strdup(mini, var->content);
		var = var->next;
	}
	tab[i] = NULL;
	return (tab);
}
