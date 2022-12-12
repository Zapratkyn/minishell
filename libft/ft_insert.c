/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 10:44:21 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/02 13:55:32 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

char	*ft_insert(t_mini *mini, char *s1, char c, char *s2)
{
	char	*ins;
	int		l1;
	int		l2;
	int		i;

	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	ins = malloc (sizeof(char) * (l1 + l2 + 2));
	if (!ins)
		ft_error(mini, MALLOC_ERR, EXIT);
	i = -1;
	while (++i < l1)
		ins[i] = s1[i];
	ins[i] = c;
	while (++i - 1 - l1 < l2)
		ins[i] = s2[i - 1 - l1];
	ins[i] = 0;
	return (ins);
}
