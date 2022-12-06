/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:36:27 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/06 13:08:22 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

static int	count_words(char *s, int i, int count, char c)
{
	while (s[i] && s[i] == ' ')
			i++;
	while (s[i] && s[i] != PIPE)
	{
		while (s[i] && s[i] == ' ')
			i++;
		if (s[i] && s[i] != ' ' && s[i] != PIPE)
		{
			count++;
			while (s[i] && s[i] != PIPE && s[i] != ' ')
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
	}
	return (count);
}

static int	find_next_len(char *str, int len, int i, char c)
{
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && str[i] != PIPE && str[i] != ' ')
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
			len++;
			i++;
		}
		i++;
		len++;
	}
	return (len);
}

static char	*find_next_word(t_mini *mini, char *s, int len)
{
	char		*result;
	int			i;

	i = 0;
	result = malloc (sizeof(char) * len + 1);
	if (!result)
		ft_error(mini, MALLOC_ERR, EXIT);
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

char	**ft_split_cmd(t_mini *mini, char *s, int i, int index)
{
	char	**tab;
	int		wc;
	int		len;

	wc = count_words(s, 0, 0, 0);
	tab = malloc(sizeof(char *) * wc + 1);
	if (!tab)
		ft_error(mini, MALLOC_ERR, EXIT);
	while (i < wc)
	{
		len = find_next_len(&s[index], 0, 0, 0);
		tab[i] = find_next_word(mini, &s[index], 0);
		index += ft_strlen(tab[i]);
		while (s[index] == ' ')
			index++;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
