/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 13:13:13 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/02 13:55:32 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

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

char	*ft_strnstr2(const char *haystack, const char *needle, size_t len)
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
				return (&hs[i + k + 1]);
			k++;
		}
		i++;
	}
	return (0);
}
