/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 12:30:54 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/13 12:30:46 by gponcele         ###   ########.fr       */
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

char	*ft_strchr_minishell(const char *s, int c, char k)
{
	int				i;
	unsigned char	ch;
	char			*str;

	i = 0;
	ch = (unsigned char)c;
	str = (char *)s;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == S_QUOTE)
		{
			k = s[i++];
			while (s[i] != k)
				i++;
			i++;
		}
		else if (s[i] == ch)
			return (&str[i]);
		else
			i++;
	}
	if (s[i] == ch)
		return (&str[i]);
	return (0);
}
