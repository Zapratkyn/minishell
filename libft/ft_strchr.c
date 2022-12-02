/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 12:30:54 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/02 13:55:32 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	ch;
	char			*str;

	i = 0;
	ch = (unsigned char)c;
	str = (char *)s;
	while (s[i])
	{
		if (str[i] == ch)
			return (&str[i]);
		else
			i++;
	}
	if (s[i] == ch)
		return (&str[i]);
	return (0);
}
