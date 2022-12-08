/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:36:27 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/08 12:42:00 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

int	quotes(char *str, char c, int i)
{
	c = str[i++];
	while (str[i] != c)
		i++;
	return (i + 2);
}

int	spike(char *str, char c, int i)
{
	c = str[i++];
	while (str[i] == c)
		i++;
	while (str[i] != ' ')
	{
		if (str[i] == '"' || str[i] == S_QUOTE)
			i += quotes(&str[i], 0, 0);
		else
			i++;
	}
	return (i);
}

static int	count_words(char *s, int i, int count, char c)
{
	while (s[i])
	{
		count++;
		while (s[i] && s[i] != ' ')
		{
			if (s[i] == S_QUOTE || s[i] == '"')
				i += quotes(&str[i], 0, 0)
			else if (s[i] == '<' || s[i] == '>')
				i += spike(&str[i], 0, 0);
			// {
			// 	c = s[i++];
			// 	while (s[i] == c)
			// 		i++;
			// 	while (s[i] != '<' && s[i] != '>' && s[i] != ' ')
			// 	{
			// 		if (s[i] == '"' || s[i] == S_QUOTE)
			// 			i += quotes(&str[i], 0, 0);
			// 		else
			// 			i++;
			// 	}
			// }
			else
				i++;
		}
		while (s[i] && s[i] == ' ')
			i++;
	}
	return (count);
}

static int	find_next_len(char *str, int i, char c)
{
	while (str[i] && str[i] != ' ' && str[i] != '<' && str[i] != '>')
	{
		if (str[i] == '"' || str[i] == S_QUOTE)
		{
			c = str[i++];
			while (str[i] != c)
				i++;
		}
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
	ICI
	tab = malloc(sizeof(char *) * wc + 1);
	if (!tab)
		return (NULL);
	while (i < wc)
	{
		len = find_next_len(&s[index], 0, 0);
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
