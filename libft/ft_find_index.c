/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_index.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 11:50:59 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/30 12:07:08 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_find_index(char *s, char c)
{
	int	i;

	i = -1;
	while (s && s[++i])
		if (s[i] == c)
			return (i);
	return (-1);
}
