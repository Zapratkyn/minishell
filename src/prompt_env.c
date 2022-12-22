/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:24:11 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/22 16:20:11 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

int	mini_get_status(t_mini *mini, char *var, int j)
{
	char	*s;
	int		i;

	if (var[0] != '?')
		return (0);
	i = 0;
	s = ft_itoa(mini, g_status);
	mini->tempstr5 = ft_strdup(mini, s);
	free (s);
	while (var[++i])
		mini->tempstr5 = ft_strjoin2(mini, mini->tempstr5, var[i]);
	if (j == 1)
		mini->tempstr5 = ft_free(mini->tempstr5);
	return (1);
}

char	*mini_getenv(t_mini *mini, char *var)
{
	t_var	*tmp;
	int		i;

	tmp = mini->var;
	i = 0;
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
	prompt = ft_strjoin(mini, prompt, ") $ ");
	prompt = ft_strjoin(mini, prompt, WHITE);
	return (prompt);
}

void	put_shell(void)
{
	printf(GREEN);
	printf("\n███╗   ███╗██╗███╗   ██╗██╗");
	printf("███████╗██╗  ██╗███████╗██╗     ██╗     \n");
	printf("████╗ ████║██║████╗  ██║██║██╔════╝");
	printf("██║  ██║██╔════╝██║     ██║     \n");
	printf("██╔████╔██║██║██╔██╗ ██║██║███████╗");
	printf("███████║█████╗  ██║     ██║     \n");
	printf("██║╚██╔╝██║██║██║╚██╗██║██║╚════██║");
	printf("██╔══██║██╔══╝  ██║     ██║     \n");
	printf("██║ ╚═╝ ██║██║██║ ╚████║██║███████║");
	printf("██║  ██║███████╗███████╗███████╗\n");
	printf("╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝");
	printf("╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n\n");
	printf(RESET);
}

char	*get_prompt(t_mini *mini, char *prompt, char *str)
{
	(void) str;
	if (prompt)
		free (prompt);
	prompt = ft_strjoin(mini, ft_strdup(mini, CYAN), "minishell");
	prompt = status_prompt(mini, prompt);
	return (prompt);
}
