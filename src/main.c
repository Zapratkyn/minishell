/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:24:11 by gponcele          #+#    #+#             */
/*   Updated: 2022/11/30 16:29:05 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

int	get_var(t_mini *mini, char *str)
{
	t_var		*index;
	t_var		*temp;

	index = mini->var;
	temp = malloc (sizeof(t_var));
	if (!temp)
		return (0);
	temp->content = ft_strdup(str);
	if (!temp->content)
		return (0);
	if (!mini->var)
		mini->var = temp;
	else
	{
		while (index->next)
			index = index->next;
		index->next = temp;
	}
	return (1);
}

char	*get_prompt(t_mini *mini)
{
	char	*str;
	char	*prompt;

	if (mini && mini->prompt)
		free(mini->prompt);
	prompt = NULL;
	prompt = ft_strdup(getenv("USER"));
	if (prompt)
		prompt = ft_strjoin(prompt, "@minishell ");
	str = ft_strnstr2(getenv("PWD"),
			getenv("USER"), 1000);
	if (str && prompt)
	{
		prompt = ft_strjoin(prompt, "~");
		if (prompt)
			prompt = ft_strjoin(prompt, str);
	}
	else if (!str && prompt)
		prompt = ft_strjoin(prompt, getenv("PWD"));
	if (prompt)
		prompt = ft_strjoin(prompt, " % ");
	return (prompt);
}

t_mini	mini_init(char **env)
{
	t_mini	mini;
	int		i;

	i = 0;
	mini.cmd = NULL;
	mini.var = NULL;
	while (env && env[i])
	{
		if (!get_var(&mini, env[i++]))
			ft_free_env(mini.var);
	}
	mini.g_status = 0;
	mini.prompt = NULL;
	mini.prompt = get_prompt(&mini);
	return (mini);
}

int	mini_parser(t_mini *mini, char *str)
{
	if (!str)
		return (0);
	if (start_with_pipe(str, 0) || !mini)
	{
		free (str);
		return (1);
	}
	if (is_input(str))
	{
		mini->cmd = get_cmd(mini, mini->cmd, str, -1);
		free (str);
		if (!mini->cmd)
			return (1);
		// execute(mini);
		mini_unlink("./heredocs/heredoc_");
	}
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	t_mini	mini;

	mini = mini_init(env);
	if (!mini.prompt || !mini.var)
		exit (EXIT_FAILURE);
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
