/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:24:11 by gponcele          #+#    #+#             */
/*   Updated: 2022/11/21 13:39:51 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

void    mini_env(t_mini *mini)
{
    t_var   *temp;

    temp = mini->var;
    while (temp)
    {
        printf("%s\n", temp->content);
        temp = temp->next;
    }
}

int	is_var(t_mini *mini, char *var, int len)
{
	t_var	*temp;

	temp = mini->var;
	while (temp)
	{
		if (ft_strncmp(temp->content, var, len) && temp->content[len] == "=")
			return (1)
		temp = temp->next;
	}
	return (0);
}

void	edit_var(t_mini *mini, char *var, int len, char *val)
{
	t_var	temp;

	temp = mini->var;
	while (ft_strncmp(temp->content, var, len) || temp->content[len] != '=')
        temp = temp->next;
	temp->content = ft_strjoin(var, "=");
	temp->content = ft_strjoin(temp->content, val);
}

void	mini_export(t_mini *mini, char *var, char *val)
{
	t_var	*temp;
	t_var	*index;
	int		len;

	index = mini->var;
	len = ft_strlen(var);
	if (!is_var(mini, var, len))
	{
		temp = malloc (sizeof(t_var));
		if (!temp)
			exit (EXIT_FAILURE);
		temp->content = var;
		temp->custom = 1;
		while (ft_strncmp(index->content, var, len) < 0)
			index = index->next;
		temp->next = index->next;
		index->next = temp;
	}
	else
		edit_var(mini, var, len, val);
}