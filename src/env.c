/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:24:11 by gponcele          #+#    #+#             */
/*   Updated: 2022/11/25 15:28:02 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

int	is_var(t_mini *mini, char *var, int j)
{
	int		i;
	int		len;
	t_var	*temp;

	i = 0;
	len = 0;
	temp = mini->var;
	while (ft_isalnum(var[i]) || var[i] == '_')
	{
		len++;
		i++;
	}
	if (j == 1)
		return (len);
	while (temp->next && j == 0)
	{
		if (!ft_strncmp(temp->content, var, len) && temp->content[len] == '=')
			return (1);
		temp = temp->next;
	}
	return (0);
}

// void	edit_var(t_mini mini, char *var, char *val)
// {
// 	t_var	*temp;
// 	int		len;

// 	temp = mini->var;
// 	len = ft_strlen(var);
// 	while (ft_strncmp(temp->content, var, len) || temp->content[len] != '=')
//         temp = temp->next;
// 	temp->content = ft_strjoin(var, "=");
// 	temp->content = ft_strjoin(temp->content, val);
// }

// int	is_varname(char *str)
// {
// 	int	i;

// 	i = 1;
// 	if (!ft_isalnum(str[0]) && str[0] != '_' && str[0] != ' ')
// 	{
// 		printf("export: << %s >> : bad variable name", str);
// 		return (0);
// 	}
// 	while (str[i] && str[i] != '=' && str[i] != '$')
// 	{
// 		if (!ft_isalnum(str[i] && str[i] != '_'))
// 			return (0);
// 		i++;
// 	}
// 	if (str[0] == ' ')
// 	{
// 		printf("export: << %s >> : bad variable name", str);
// 		return (0);
// 	}
// 	return (1);
// }

// void	mini_export(t_mini *mini, char *var, char *val)
// {
// 	t_var	*temp;
// 	t_var	*index;

// 	index = mini->var;
// 	if (!var && !val)
// 		mini_env(mini, 1);
// 	else if (!is_var(mini, var) && is_varname(var))
// 	{
// 		temp = malloc (sizeof(t_var));
// 		if (!temp)
// 			exit (EXIT_FAILURE);
// 		temp->content = ft_strdup(ft_varname(var));
// 		temp->custom = 1;
// 		while (ft_strncmp(index->content, var, ft_strlen(var)) < 0)
// 			index = index->next;
// 		temp->next = index->next;
// 		index->next = temp;
// 	}
// 	if (is_var(mini, var))
// 		edit_var(mini, var, val);
// }