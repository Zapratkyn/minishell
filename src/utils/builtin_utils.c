/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 11:05:17 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/02 11:27:56 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minish.h"

char	*ft_rev_strchr(char *str, char c)
{
	int	i;

	i = -1;
	while (str && str[++i])
		if (str[i] == c)
			return (ft_substr(str, 0, i));
	return (NULL);
}

int	is_env(t_mini *mini, char *s)
{
	t_var	*var;
	int		i;

	var = mini->var;
	while (var)
	{
		i = -1;
		while (var->content[++i])
			if (var->content[i] == '=')
				break ;
		if (!ft_strncmp(var->content, s, i))
			return (1);
		var = var->next;
	}
	return (0);
}
