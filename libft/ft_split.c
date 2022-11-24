/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:40:56 by gponcele          #+#    #+#             */
/*   Updated: 2022/07/18 12:26:42 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static char	**ft_free(int index, char **split)
{
	while (--index)
		free(split[index]);
	free(split);
	return (NULL);
}

static char	*find_next_word(char *s, char c, int index)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (index)
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			index--;
		while (index && s[i] && s[i] != c)
			i++;
	}
	j = i;
	while (s[j] && s[j] != c)
	{
		count++;
		j++;
	}
	return (ft_substr(&s[i], 0, count));
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		i;
	int		wc;

	if (!s)
		return (0);
	i = -1;
	wc = count_words(s, c);
	if (!s)
		return (NULL);
	str = malloc(sizeof(char *) * (wc + 1));
	if (!str)
		return (NULL);
	while (++i < wc)
	{
		str[i] = find_next_word((char *)s, c, i + 1);
		if (!str[i])
			return (ft_free(i, str));
	}
	str[i] = 0;
	return (str);
}
