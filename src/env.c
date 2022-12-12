/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:24:11 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/12 11:21:34 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

int	is_var(t_mini *mini, char *var, int j)
{
	int		i;
	t_var	*temp;

	i = 0;
	temp = mini->var;
	if (var[0] == '?')
		return (1);
	while (var[i] && (ft_isalnum(var[i]) || var[i] == '_'))
		i++;
	if (j == 1)
		return (i);
	while (temp->next && j == 0)
	{
		if (!ft_strncmp(temp->content, var, i) && temp->content[i] == '=')
			return (1);
		temp = temp->next;
	}
	return (0);
}

char	*mini_getenv(t_mini *mini, char *var)
{
	t_var	*tmp;
	int		i;
	char	*s;

	tmp = mini->var;
	i = 0;
	if (var[0] == '?')
	{
		s = ft_itoa(mini, g_status);
		while (var[++i])
			s = ft_strjoin2(mini, s, var[i]);
		return (s);
	}
	while (ft_isalnum(var[i]) || var[i] == '_')
		i++;
	while (tmp->next)
	{
		if (!ft_strncmp(var, tmp->content, i) && tmp->content[i] == '=')
			return (&tmp->content[i + 1]);
		tmp = tmp->next;
	}
	return (NULL);
}
