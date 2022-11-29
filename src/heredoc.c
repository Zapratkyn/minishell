/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:12:17 by gponcele          #+#    #+#             */
/*   Updated: 2022/11/28 16:50:43 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

void	heredoc_c(int sig)
{
	char	*prompt;

	(void)sig;
	g_status = 1;
	prompt = get_prompt();
	write (1, "\n", 1);
	write (1, prompt, ft_strlen(prompt));
	// rl_replace_line("", 0);
	free (prompt);
}

char	*join_hd(char *hd, char *str)
{
	char	*result;

	if (!str)
		return (NULL);
	result = ft_strjoin(hd, str);
	result = ft_strjoin(result, "\n");
	return (result);
}

char	*heredoc(char *end, char *str)
{
	char	*hd;

	hd = calloc(1, 1);
	while (1 && g_status == 0)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, heredoc_c);
		if (!join_hd(hd, readline(">")))
			return (NULL);
		if (!ft_strcmp(hd, end) && ft_strlen(hd) == ft_strlen(end))
			break ;
	}
	if (g_status != 0)
		return (NULL);
	return (ft_strjoin(hd, str));
}

int	mini_heredoc(char *str, int i, int j)
{
	char	*end;
	char	*hd;
	char	*result;

	result = calloc(1, 1);
	end = calloc(1, 1);
	if (!result || !end)
		return (0);
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<')
		{
			j = i + 2;
			while (str[j] == ' ')
				j++;
			while (str[j] && str[j] != ' ')
				end = ft_strjoin2(end, str[j++]);
			hd = &str[i];
			hd = heredoc(end, &str[j]);
			if (!hd)
				return (0);
		}
		else
			result = ft_strjoin2(result, str[i++]);
	}
	return (1);
}
