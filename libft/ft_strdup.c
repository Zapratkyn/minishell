/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 18:07:27 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/07 17:50:51 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

char	*ft_strdup(t_mini *mini, char *str)
{
	char	*result;
	int		i;

	result = malloc (sizeof(char) * (ft_strlen(str) + 1));
	if (!result)
		ft_error(mini, MALLOC_ERR, EXIT);
	i = 0;
	while (str && str[i])
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_strdup2(t_mini *mini, char *str)
{
	char	*result;
	int		i;

	result = malloc (sizeof(char) * ft_strlen(str));
	if (!result)
		ft_error(mini, MALLOC_ERR, EXIT);
	i = 0;
	while (str[i + 1])
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
