/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:24:11 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/07 17:42:31 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

int	get_var(t_mini *mini, char **env)
{
	int		i;
	t_var	*var;

	i = 0;
	mini->var = ft_lstnew(mini, env[i]);
	while (env[++i])
		ft_lstadd_back(&mini->var, ft_lstnew(mini, ft_strdup(mini, env[i])));
	var = mini->var;
	while (var)
	{
		if (var->next)
			var->next->prev = var;
		var = var->next;
	}
	return (1);
}

char	*get_prompt(t_mini *mini, char *prompt)
{
	char	*str;

	if (prompt)
		free (prompt);
	prompt = ft_strjoin(mini, ft_strdup(mini, GREEN), getenv("USER"));
	if (prompt)
		prompt = ft_strjoin(mini, prompt, "@minishell ");
	str = ft_strnstr2(mini_getenv(mini, "PWD"),
			mini_getenv(mini, "USER"), INT_MAX);
	if (str && prompt)
	{
		prompt = ft_strjoin(mini, prompt, "~");
		prompt = ft_strjoin(mini, prompt, str);
	}
	else if (!str && prompt)
		prompt = ft_strjoin(mini, prompt, mini_getenv(mini, "PWD"));
	prompt = ft_strjoin(mini, prompt, " % ");
	prompt = ft_strjoin(mini, prompt, WHITE);
	return (prompt);
}

void	mini_init(t_mini *mini, char **env)
{

	mini->cmd = NULL;
	mini->var = NULL;
	if (!get_var(mini, env))
		ft_lstclear(&mini->var);
	mini->paths = ft_split(mini, mini_getenv(mini, "PATH"), ':');
	if (!mini->paths || !mini->var)
		exit (EXIT_FAILURE);
	mini->g_status = 0;
	mini->prompt = NULL;
	mini->prompt = get_prompt(mini, mini->prompt);
	if (!mini->prompt)
	{
		ft_lstclear(mini->var);
		ft_free_tab(mini->paths, ft_tablen(mini->paths));
		exit (EXIT_FAILURE);
	}
}

int	mini_parser(t_mini *mini, char *str)
{
	if (!str)
		return (0);
	if (start_with_pipe(mini, str, 0) || !mini)
	{
		if (str)
			free (str);
		return (1);
	}
	if (is_input(str))
	{
		mini->cmd = get_cmd(mini, mini->cmd, str, -1);
			execute(mini);
		mini->cmd = ft_free_cmd(mini->cmd);
		mini_unlink(mini, "/tmp/mini_heredocs/heredoc_");
	}
	free (str);
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	t_mini	mini;

	mini_init(&mini, env);
	g_status = 0;
	while (argc && argv[0])
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, mini_new_line);
		if (!mini_parser(&mini, readline(mini.prompt)))
			break ;
	}
	ft_free_all(&mini);
	write(STDERR_FILENO, "\nexit\n", 6);
	exit(g_status);
}
