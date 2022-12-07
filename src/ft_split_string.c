/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:51:46 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/07 12:21:55 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

static int	count_words(char *s, int i, int count, char c)
{
	while (s[i])
	{
		count++;
		if (s[i] == S_QUOTE || s[i] == '"')
		{
			c = s[i++];
			while (s[i] != c)
				i++;
			i++;
		}
		else if (s[i] == '$')
		{
			i++;
			while (isalnum(s[i]) || s[i] == '_' || s[i] == '?')
				i++;
		}
		else
		{
			while (s[i] && s[i] != '$' && s[i] != S_QUOTE && s[i] != '"')
				i++;
		}
		while (s[i] && s[i] == ' ')
			i++;
	}
	return (count);
}

static int	find_next_len(char *s, int i, char c)
{
	if (s[0] == '$')
	{
		i++;
		while (isalnum(s[i]) || s[i] == '_' || s[i] == '?')
			i++;
	}
	else if (s[0] == S_QUOTE || s[0] == '"')
	{
		c = s[0];
		i++;
		while (s[i] != c)
			i++;
		i++;
	}
	else if (s[0] && s[0] != '$' && s[i] != S_QUOTE && s[i] != '"')
	{
		while (s[i] && s[i] != '$' && s[i] != S_QUOTE && s[i] != '"')
			i++;
	}
	return (i);
}

static char	*find_next_word(char *s, int i, int len)
{
	char		*result;

	result = malloc (sizeof(char) * len + 1);
	if (!result)
		return (NULL);
	while (i < len)
	{
		result[i] = s[i];
		i++;
	}
	result[len] = '\0';
	return (result);
}

char	**split_string(char *s, int i, int index, int len)
{
	char	**tab;
	int		wc;

	wc = count_words(s, 0, 0, 0);
	tab = malloc(sizeof(char *) * (wc + 1));
	if (!tab)
		return (NULL);
	while (i < wc)
	{
		len = find_next_len(&s[index], 0, 0);
		tab[i] = find_next_word(&s[index], 0, len);
		if (!tab[i])
			return (NULL);
		index += ft_strlen(tab[i]);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
