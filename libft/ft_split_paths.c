/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_paths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 18:23:28 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/13 21:20:14 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

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

static char	*find_next_word(t_mini *mini, char *s, char c, int index)
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
	return (ft_substr(mini, &s[i], 0, count));
}

void	ft_split_paths(t_mini *mini, char const *s, char c)
{
	int		i;
	int		wc;

	if (!s)
		return ;
	i = -1;
	wc = count_words(s, c);
	mini->paths = malloc(sizeof(char *) * (wc + 1));
	if (!mini->paths)
		ft_error(mini, MALLOC_ERR, EXIT);
	while (++i < wc)
	{
		mini->paths[i] = find_next_word(mini, (char *)s, c, i + 1);
		if (!mini->paths[i])
			ft_error(mini, MALLOC_ERR, EXIT);
	}
	mini->paths[i] = NULL;
}
