/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:51:46 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/06 13:10:46 by ademurge         ###   ########.fr       */
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
			c = s[i];
			i++;
			while (s[i] != c)
				i++;
			i++;
		}
		else if (s[i] == '$')
		{
			i++;
			while (ft_isalnum(s[i]) || s[i] == '_' || s[i] == '?')
				i++;
		}
		else
		{
			while (s[i] && s[i] != '$' && s[i] != S_QUOTE)
				i++;
		}
	}
	return (count);
}

static int	find_next_len(char *s, int i, char c)
{
	if (s[0] == '$')
	{
		i++;
		while (ft_isalnum(s[i]) || s[i] == '_' || s[i] == '?')
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
	else if (s[0] != '$' && s[i] != S_QUOTE)
	{
		while (s[i] && s[i] != '$' && s[i] != S_QUOTE)
			i++;
	}
	return (i);
}

static char	*find_next_word(t_mini *mini, char *s, int i, int len)
{
	char		*result;

	result = malloc (sizeof(char) * len + 1);
	if (!result)
		ft_error(mini, MALLOC_ERR, EXIT);
	while (i < len)
	{
		result[i] = s[i];
		i++;
	}
	result[len] = '\0';
	return (result);
}

char	**split_string(t_mini *mini, char *s, int i, int index)
{
	char	**tab;
	int		wc;
	int		len;

	len = 0;
	wc = count_words(s, 0, 0, 0);
	tab = malloc(sizeof(char *) * (wc + 1));
	if (!tab)
		ft_error(mini, MALLOC_ERR, EXIT);
	while (i < wc)
	{
		len = find_next_len(&s[index], 0, 0);
		tab[i] = find_next_word(mini, &s[index], 0, 0);
		index += ft_strlen(tab[i]);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
