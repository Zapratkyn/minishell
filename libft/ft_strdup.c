/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 18:07:27 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/06 12:33:12 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *str)
{
	char	*result;
	int		i;

	result = malloc (sizeof(char) * ft_strlen(str) + 1);
	if (!result)
		return (0);
	i = 0;
	while (str[i])
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_strdup2(char *str)
{
	char	*result;
	int		i;

	result = malloc (sizeof(char) * ft_strlen(str));
	if (!result)
		return (0);
	i = 0;
	while (str[i + 1])
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
