/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:36:27 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/01 18:57:00 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

int	quote_len(char *str, char c)
{
	int	i;

	i = 1;
	while (str[i] != c)
		i++;
	return (i + 1);
}

static int	count_words(char *s, int i, int count, char c)
{
	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
			i++;
	while (s[i] && s[i] != PIPE)
	{
		while (s[i] && (s[i] == ' ' || s[i] == '\t'))
			i++;
		if (s[i] && s[i] != ' ' && s[i] != PIPE)
		{
			count++;
			i++;
			while (s[i] && s[i] != ' ' && s[i] != PIPE)
			{
				if (s[i] == '"' || s[i] == S_QUOTE)
				{
					c = s[i];
					while (s[i] != c)
						i++;
					i++;
				}
				else
					i++;
			}
			// if (s[i] == S_QUOTE || s[i] == '"')
			// 	i += quote_len(&s[i], s[i]);
			// else
			// {
			// 	while (s[i] == '<' || s[i] == '>')
			// 		i++;
			// 	while (s[i] && s[i] != ' ' && s[i] != PIPE
			// 		&& s[i] != '<' && s[i] != '>')
			// 		i++;
			// }
		}
	}
	return (count);
}

static int	find_next_len(char *str, int i, int len)
{
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] == '"')
	{
		i++;
		while (str[i++] != '"')
			len++;
		return (len + 3);
	}
	else if (str[i] == S_QUOTE)
	{
		i++;
		while (str[i++] != S_QUOTE)
			len++;
		return (len + 3);
	}
	while (str[i] && str[i] != PIPE && str[i] != ' ')
	{
		len++;
		i++;
	}
	return (len + 1);
}

static char	*find_next_word(char *s, int len)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc (sizeof(char) * len);
	if (!str)
		return (0);
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	s = &s[i];
	i = 0;
	while (i < (len - 1))
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split_cmd(char *s, int i, int index, int len)
{
	char	**tab;
	int		wc;

	wc = count_words(s, 0, 0, 0);
	tab = malloc(sizeof(char *) * wc + 1);
	if (!tab)
		return (NULL);
	while (s[index] == ' ')
		index++;
	while (i < wc)
	{
		len = find_next_len(&s[index], 0, 0);
		tab[i] = find_next_word(&s[index], len);
		if (!tab[i])
		{
			ft_free_full_cmd(tab);
			return (NULL);
		}
		index += (len - 1);
		while (s[index] == ' ' || s[index] == '\t')
			index++;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
