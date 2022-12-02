/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 18:07:27 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/02 13:55:32 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

char	*ft_calloc(t_mini *mini, int count, int size)
{
	char	*result;
	int		i;

	i = 0;
	result = malloc (size * count);
	if (!result)
		ft_error(mini, MALLOC_ERR, EXIT);
	while (i < count)
		result[i++] = '\0';
	return (result);
}
