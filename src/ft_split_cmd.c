/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:36:27 by gponcele          #+#    #+#             */
/*   Updated: 2022/11/23 15:32:36 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

int	is_quote(char *str, char c)
{
	int	i;

	i = 1;
	while (str[i] != c)
		i++;
	return (i);
}

static int	count_words(char *s, int i, int count)
{
	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
			i++;
	while (s[i] && s[i] != PIPE)
	{
		while (s[i] && (s[i] == ' ' || s[i] == '\t'))
			i++;
		if (s[i] && s[i] != ' ' && s[i] != '\t' && s[i] != PIPE)
		{
			count++;
			if (s[i] == S_QUOTE || s[i] == '"')
				i += is_quote(&s[i], s[i]);
			i++;
		}
		while (s[i] && s[i] != ' ' && s[i] != PIPE && s[i] != '\t')
			i++;
	}
	return (count);
}

int	find_next_len(char *str, int i, int len)
{
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] == '"')
	{
		i++;
		while (str[i++] != '"')
			len++;
		return (len + 1);
	}
	else if (str[i] == S_QUOTE)
	{
		i++;
		while (str[i++] != S_QUOTE)
			len++;
		return (len + 1);
	}
	while (str[i] && str[i] != PIPE && str[i] != ' ' && str[i] != '\t')
	{
		len++;
		i++;
	}
	return (len);
}

static char	*find_next_word(char *s, int len)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc (sizeof(char) * len + 1);
	if (!str)
		return (0);
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	s = &s[i];
	i = 0;
	while (i <= len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split_cmd(char *s, int i, int index)
{
	char	**tab;
	int		wc;
	int		j;

	j = 0;
	wc = count_words(s, 0, 0);
	printf("%d\n", wc);
	tab = malloc(sizeof(char *) * wc + 1);
	if (!tab)
		return (NULL);
	while (i < wc)
	{
		j = find_next_len(&s[index], 0, 0);
		tab[i] = find_next_word(&s[index], j);
		if (!tab[i])
			ft_free_full_cmd(tab);
		index += (j + 1);
		while (s[index] == ' ' || s[index] == '\t')
			index++;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
