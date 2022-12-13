/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:24:11 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/13 12:32:09 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

int	is_var(t_mini *mini, char *var)
{
	int		i;
	t_var	*temp;

	i = 0;
	temp = mini->var;
	if (var[0] == '?')
		return (1);
	while (var[i] && (ft_isalnum(var[i]) || var[i] == '_'))
		i++;
	while (temp)
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
	while (tmp)
	{
		if (!ft_strncmp(var, tmp->content, i) && tmp->content[i] == '=')
			return (&tmp->content[i + 1]);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*status_prompt(t_mini *mini, char *prompt)
{
	char	*nb;

	if (!g_status)
		prompt = ft_strjoin(mini, prompt, GREEN);
	else
		prompt = ft_strjoin(mini, prompt, RED);
	prompt = ft_strjoin(mini, prompt, " (");
	nb = ft_itoa(mini, g_status);
	prompt = ft_strjoin(mini, prompt, nb);
	free(nb);
	prompt = ft_strjoin(mini, prompt, ") > ");
	prompt = ft_strjoin(mini, prompt, WHITE);
	return (prompt);
}

char	*get_prompt(t_mini *mini, char *prompt)
{
	char	*str;

	if (prompt)
		free (prompt);
	prompt = ft_strjoin(mini, ft_strdup(mini, BLUE), getenv("USER"));
	prompt = ft_strjoin(mini, prompt, "@minishell ");
	str = ft_strnstr2(mini_getenv(mini, "PWD"),
			mini_getenv(mini, "USER"), INT_MAX);
	if (str && prompt)
	{
		prompt = ft_strjoin(mini, prompt, GREEN);
		prompt = ft_strjoin(mini, prompt, "~");
		prompt = ft_strjoin(mini, prompt, str);
	}
	else if (!str && prompt)
		prompt = ft_strjoin(mini, prompt, mini_getenv(mini, "PWD"));
	prompt = status_prompt(mini, prompt);
	return (prompt);
}
