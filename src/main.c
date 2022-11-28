/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:24:11 by gponcele          #+#    #+#             */
/*   Updated: 2022/11/28 16:54:50 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

void	get_var(t_mini *mini, char *str)
{
	t_var		*index;
	t_var		*temp;

	index = mini->var;
	temp = malloc (sizeof(t_var));
	if (!temp)
		exit (0);
	temp->content = ft_strdup(str);
	if (!temp->content)
		exit (0);
	if (!mini->var)
		mini->var = temp;
	else
	{
		while (index->next)
			index = index->next;
		index->next = temp;
	}
}

char	*get_prompt(t_mini *mini)
{
	char	*str;
	char	*prompt;

	if (mini->prompt)
		free (mini->prompt);
	prompt = ft_strdup(mini_getenv(mini, "USER"));
	prompt = ft_strjoin(prompt, "@minishell ");
	str = ft_strnstr2(mini_getenv(mini, "PWD"),
			mini_getenv(mini, "USER"), 1000);
	if (str)
	{
		prompt = ft_strjoin(prompt, "~");
		prompt = ft_strjoin(prompt, str);
	}
	else
		prompt = ft_strjoin(prompt, mini_getenv(mini, "PWD"));
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
		get_var(&mini, env[i++]);
	mini.g_status = 0;
	mini.prompt = NULL;
	mini.prompt = get_prompt(&mini);
	return (mini);
}

int	mini_parser(t_mini *mini, char *str)
{
	if (!str)
		return (0);
	if (start_with_pipe(str))
		return (1);
	if (is_input(str))
	{
		add_history(str);
		mini->cmd = get_cmd(mini, mini->cmd, str, 0);
		execute(mini);
	}
	free (str);
	mini->prompt = get_prompt(mini);
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	t_mini	mini;

	mini = mini_init(env);
	while (argc && argv[0])
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, mini_new_line);
		if (!mini_parser(&mini, readline(mini.prompt)))
			break ;
	}
	mini_exit(&mini);
}
