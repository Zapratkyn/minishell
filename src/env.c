/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:24:11 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/08 11:23:47 by ademurge         ###   ########.fr       */
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

	tmp = mini->var;
	if (var[0] == '?')
		return (ft_itoa(mini, g_status));
	i = 0;
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
