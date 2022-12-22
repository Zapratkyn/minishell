/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:36:27 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/22 17:13:11 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

int	spike(char *str, char c, int i)
{
	c = str[i++];
	while (str[i] && str[i] == c)
		i++;
	while (str[i] && str[i] != ' ')
	{
		if (str[i] == '"' || str[i] == S_QUOTE)
			i += quotes(&str[i], 0, 0);
		else
			i++;
	}
	return (i);
}

int	count_words(char *s, int i, int count)
{
	while (s[i])
	{
		count++;
		if (s[i] == '<' || s[i] == '>')
			i += spike(&s[i], 0, 0);
		else
		{
			while (s[i] && s[i] != ' ' && s[i] != '<' && s[i] != '>')
			{
				if (s[i] == S_QUOTE || s[i] == '"')
					i += quotes(&s[i], 0, 0);
				else
					i++;
			}
		}
		while (s[i] && s[i] == ' ')
			i++;
	}
	return (count);
}

int	find_next_len(char *s, int i)
{
	if (s[i] == '<' || s[i] == '>')
		i += spike(&s[i], 0, 0);
	else
	{
		while (s[i] && s[i] != ' ' && s[i] != '<' && s[i] != '>')
		{
			if (s[i] == S_QUOTE || s[i] == '"')
				i += quotes(&s[i], 0, 0);
			else
				i++;
		}
	}
	return (i);
}

static char	*find_next_word(t_mini *mini, char *input, char *s, int len)
{
	char		*result;
	int			i;

	i = 0;
	result = malloc (sizeof(char) * len + 1);
	if (!result)
	{
		free (input);
		ft_error(mini, MALLOC_ERR, EXIT);
	}
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
	wc = count_words(&s[index], 0, 0);
	tab = malloc(sizeof(char *) * (wc + 1));
	if (!tab)
	{
		free (s);
		ft_error(mini, MALLOC_ERR, EXIT);
	}
	while (i < wc)
	{
		len = find_next_len(&s[index], 0);
		tab[i] = find_next_word(mini, s, &s[index], len);
		index += ft_strlen(tab[i]);
		while (s[index] == ' ')
			index++;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
