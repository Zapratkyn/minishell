/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:24:11 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/14 11:38:16 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

int	get_var(t_mini *mini, char **env)
{
	int		i;
	t_var	*var;

	i = 0;
	mini->var = ft_lstnew(mini, ft_strdup(mini, env[i]));
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

void	mini_init(t_mini *mini, char **env)
{
	mini->cmd = NULL;
	mini->var = NULL;
	mini->tempstr = NULL;
	mini->tempstr2 = NULL;
	mini->tempstr3 = NULL;
	mini->tempstr4 = NULL;
	mini->tempstr5 = NULL;
	mini->temptab = NULL;
	if (!get_var(mini, env))
		ft_lstclear(mini->var);
	ft_split_paths(mini, mini_getenv(mini, "PATH"), ':');
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
	if (ft_strlen(str) != 0)
		add_history(str);
	if (ft_pipes(str, 0) || ft_pipes2(str, (ft_strlen(str) - 1)))
	{
		free (str);
		return (1);
	}
	if (is_input(mini, str))
	{
		mini->cmd = get_cmd(mini, mini->cmd, str, -1);
		execute(mini);
		mini->cmd = ft_free_cmd(mini->cmd);
		mini_unlink(mini, "/tmp/heredoc_");
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
		signal(SIGTSTP, SIG_IGN);
		signal(SIGINT, mini_new_line);
		if (!mini_parser(&mini, readline(mini.prompt)))
			break ;
		mini.prompt = get_prompt(&mini, mini.prompt);
	}
	ft_free_all(&mini);
	write(STDERR_FILENO, "exit\n", 6);
	LEAKS
	exit(g_status);
}
