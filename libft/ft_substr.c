/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 18:22:47 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/02 13:31:29 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(t_mini *mini, char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	j;
	size_t	str_len;

	if (!s)
		return (NULL);
	if (len >= ft_strlen(s))
		str_len = ft_strlen(s);
	else
		str_len = len;
	substr = malloc (sizeof(char) * (str_len + 1));
	if (!substr)
		ft_error(mini, MALLOC_ERR, EXIT);
	i = ((size_t)start);
	j = 0;
	while (i < ft_strlen(s) && j < len)
	{
		substr[j] = s[i];
		i++;
		j++;
	}
	substr[j] = '\0';
	return (substr);
}
