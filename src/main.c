/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:24:11 by gponcele          #+#    #+#             */
/*   Updated: 2022/11/30 14:52:51 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

void	get_var(t_mini *mini, char **env)
{
	int		i;
	t_var	*var;

	i = 0;
	mini->var = ft_lstnew(env[i]);
	while (env[++i])
		ft_lstadd_back(&mini->var, ft_lstnew(env[i]));
	var = mini->var;
	while (var)
	{
		if (ft_lst_index(&mini->var, var) && !ft_lstlast(var))
			var->next->prev = var;
		var = var->next;
	}
}

char	*get_prompt(t_mini *mini)
{
	char	*str;
	char	*prompt;

	if (mini && mini->prompt)
		free(mini->prompt);
	prompt = ft_strdup(GREEN);
	prompt = ft_strjoin(prompt, getenv("USER"));
	prompt = ft_strjoin(prompt, "@minishell ");
	str = ft_strnstr2(getenv("PWD"),
			getenv("USER"), 1000);
	if (str)
	{
		prompt = ft_strjoin(prompt, "~");
		prompt = ft_strjoin(prompt, str);
	}
	else
		prompt = ft_strjoin(prompt, getenv("PWD"));
	prompt = ft_strjoin(prompt, " % ");
	prompt = ft_strjoin(prompt, WHITE);
	return (prompt);
}

t_mini	mini_init(char **env)
{
	t_mini	mini;
	int		i;

	i = 0;
	mini.cmd = NULL;
	mini.var = NULL;
	get_var(&mini, env);
	mini.g_status = 0;
	mini.prompt = NULL;
	mini.prompt = get_prompt(&mini);
	return (mini);
}

int	mini_parser(t_mini *mini, char *str)
{
	if (!str)
		return (0);
	if (start_with_pipe(str, 0))
		return (1);
	if (is_input(str))
	{
		add_history(str);
		mini->cmd = get_cmd(mini, mini->cmd, str, -1);
		execute(mini);
	}
	free (str);
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	t_mini	mini;

	mini = mini_init(env);
	g_status = 0;
	while (argc && argv[0])
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, mini_new_line);
		if (!mini_parser(&mini, readline(mini.prompt)))
			break ;
	}
	mini_exit(&mini);
}
