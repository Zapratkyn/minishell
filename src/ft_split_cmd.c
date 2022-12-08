/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:36:27 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/08 11:25:08 by ademurge         ###   ########.fr       */
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

	while (s[index] == ' ')
		index++;
	wc = count_words(&s[index], 0, 0, 0);
	tab = malloc(sizeof(char *) * wc + 1);
	if (!tab)
		ft_error(mini, MALLOC_ERR, EXIT);
	while (i < wc)
	{
		len = find_next_len(&s[index], 0, 0, 0);
		tab[i] = find_next_word(mini, &s[index], len);
		index += ft_strlen(tab[i]);
		while (s[index] == ' ')
			index++;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
