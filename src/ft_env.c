/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:24:11 by gponcele          #+#    #+#             */
/*   Updated: 2022/11/21 14:27:35 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

void    mini_env(t_mini *mini, int i)
{
    t_var   *temp;
	char	c;

    temp = mini->var;
	c = 34;
    while (temp)
    {
		if ((i == 0 && temp->custom == 0) || i == 1)
		{
			if (i == 1)
				write (1, &c, 1);
        	printf("%s\n", temp->content);
			if (i == 1)
				write (1, &c, 1);
		}
        temp = temp->next;
    }
}

int	is_var(t_mini *mini, char *var)
{
	t_var	*temp;
	int		i;
	int		len;

	temp = mini->var;
	i = 0;
	while (ft_isalnum(var[i]) || var[i] == '_')
    {
        len++;
        i++;
    }
	while (temp)
	{
		if (!ft_strncmp(temp->content, var, len) && temp->content[len] == '=')
			return (1);
		temp = temp->next;
	}
	return (0);
}

void	edit_var(t_mini *mini, char *var, char *val)
{
	t_var	*temp;
	int		len;

	temp = mini->var;
	len = ft_strlen(var);
	while (ft_strncmp(temp->content, var, len) || temp->content[len] != '=')
        temp = temp->next;
	temp->content = ft_strjoin(var, "=");
	temp->content = ft_strjoin(temp->content, val);
}

int	is_varname(char *str)
{
	int	i;

	i = 1;
	if (!ft_isalnum(str[0]) && str[0] != '_' && str[0] != ' ')
	{
		printf("export: << %s >> : identifiant non valable", str);
		return (0);
	}
	while (str[i] && str[i] != '=' && str[i] != '$')
	{
		if (!ft_isalnum(str[i] && str[i] != '_'))
			return (0);
		i++;
	}
	if (str[0] == ' ')
	{
		printf("export: << %s >> : identifiant non valable", str);
		return (0);
	}
	return (1);
}

void	mini_export(t_mini *mini, char *var, char *val)
{
	t_var	*temp;
	t_var	*index;

	index = mini->var;
	if (!var && !val)
		mini_env(mini, 1);
	else if (!is_var(mini, var) && is_varname(var))
	{
		temp = malloc (sizeof(t_var));
		if (!temp)
			exit (EXIT_FAILURE);
		temp->content = ft_strdup(ft_varname(var));
		temp->custom = 1;
		while (ft_strncmp(index->content, var, ft_strlen(var)) < 0)
			index = index->next;
		temp->next = index->next;
		index->next = temp;
	}
	if (is_var(mini, var))
		edit_var(mini, var, val);
}