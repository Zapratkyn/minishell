/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 18:07:27 by gponcele          #+#    #+#             */
/*   Updated: 2022/07/11 14:13:28 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    *ft_calloc(int count, int size)
{
    char    *result;
    int     i;

    i = 0;
    result = malloc (size * count);
    if (!result)
        return (NULL);
    while (i < count)
        result[i++] = '\0';
    return (result);
}