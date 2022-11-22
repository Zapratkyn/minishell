/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 12:30:54 by gponcele          #+#    #+#             */
/*   Updated: 2022/07/11 17:50:40 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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