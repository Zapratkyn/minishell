/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:51:46 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/13 16:10:50 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

static int	count_words(char *s, int i, int count, char c)
{
	while (s[i])
	{
		count++;
		if (s[i] == S_QUOTE || s[i] == D_QUOTE)
		{
			c = s[i++];
			while (s[i] != c)
				i++;
			i++;
		}
		else if (s[i] == '$' && s[i + 1]
			&& (ft_isalnum(s[i + 1]) || s[i + 1] == '_' || s[i + 1] == '?'))
			i += dollar(&s[i], 1, 0);
		else
			while (s[i] && s[i] != S_QUOTE && s[i] != '"' && !(s[i] == '$'
					&& s[i + 1] && (ft_isalnum(s[i + 1])
						|| s[i + 1] == '_' || s[i + 1] == '?')))
				i++;
		while (s[i] && s[i] == ' ')
			i++;
	}
	return (count);
}

static int	find_next_len(char *s, int i, char c)
{
	if (s[0] == '$' && s[1] && (ft_isalnum(s[1]) || s[1] == '_' || s[1] == '?'))
		i += dollar(s, 1, 0);
	else if (s[0] == S_QUOTE || s[0] == D_QUOTE)
	{
		c = s[0];
		i++;
		while (s[i] != c)
			i++;
		i++;
	}
	else
		while (s[i] && s[i] != S_QUOTE && s[i] != '"' && !(s[i] == '$'
				&& s[i + 1] && (ft_isalnum(s[i + 1])
					|| s[i + 1] == '_' || s[i + 1] == '?')))
			i++;
	return (i);
}

static char	*find_next_word(t_mini *mini, char *s, int i, int len)
{
	char		*result;

	result = malloc (sizeof(char) * (len + 1));
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

void	split_string(t_mini *mini, char *s, int i, int index)
{
	int		wc;
	int		len;

	len = 0;
	wc = count_words(s, 0, 0, 0);
	mini->temptab = malloc(sizeof(char *) * (wc + 1));
	if (!mini->temptab)
		ft_error(mini, MALLOC_ERR, EXIT);
	while (i < wc)
	{
		len = find_next_len(&s[index], 0, 0);
		mini->temptab[i] = find_next_word(mini, &s[index], 0, len);
		index += ft_strlen(mini->temptab[i]);
		i++;
	}
	mini->temptab[i] = NULL;
}
