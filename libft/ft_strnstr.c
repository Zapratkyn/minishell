/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 13:13:13 by gponcele          #+#    #+#             */
/*   Updated: 2022/07/12 16:52:29 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	k;
	char	*hs;
	char	*nd;

	i = 0;
	hs = (char *)haystack;
	nd = (char *)needle;
	if (nd[i] == '\0')
		return (hs);
	while (hs[i])
	{
		k = 0;
		while ((hs[i + k] == nd[k]) && ((i + k) < len))
		{
			if (nd[k + 1] == '\0')
				return (&hs[i]);
			k++;
		}
		i++;
	}
	return (0);
}