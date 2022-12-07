/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:36:27 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/07 11:59:27 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

static int	count_words(char *s, int i, int count, char c)
{
	while (s[i])
	{
		if (s[i] && s[i] != ' ')
		{
			count++;
			while (s[i] && s[i] != ' ')
			{
				if (s[i] == '"' || s[i] == S_QUOTE)
				{
					c = s[i++];
					while (s[i] != c)
						i++;
				}
				i++;
			}
		}
		while (s[i] && s[i] == ' ')
			i++;
	}
	return (count);
}

static int	find_next_len(char *str, int len, int i, char c)
{
	while (str[i] && str[i] != ' ')
	{
		if (str[i] == '"' || str[i] == S_QUOTE)
		{
			len++;
			c = str[i++];
			while (str[i] != c)
			{
				i++;
				len++;
			}
		}
		i++;
		len++;
	}
	return (len);
}

static char	*find_next_word(char *s, int i, int len)
{
	char		*result;

	result = malloc (sizeof(char) * len + 1);
	if (!result)
		return (NULL);
	while (s[i] == ' ')
		i++;
	s = &s[i];
	i = 0;
	while (i < len)
	{
		result[i] = s[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	**ft_split_cmd(char *s, int i, int index, int len)
{
	char	**tab;
	int		wc;

	while (s[index] == ' ')
		index++;
	wc = count_words(&s[index], 0, 0, 0);
	tab = malloc(sizeof(char *) * wc + 1);
	if (!tab)
		return (NULL);
	while (i < wc)
	{
		len = find_next_len(&s[index], 0, 0, 0);
		tab[i] = find_next_word(&s[index], 0, len);
		if (!tab[i])
			return (NULL);
		index += ft_strlen(tab[i]);
		while (s[index] == ' ')
			index++;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
