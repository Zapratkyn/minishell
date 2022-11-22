/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:24:11 by gponcele          #+#    #+#             */
/*   Updated: 2022/11/22 11:50:43 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

void    get_var(t_mini *mini, char *str)
{
    t_var   *index;
    t_var   *temp;

    index = mini->var;
    temp = malloc (sizeof(t_var));
    if (!temp)
        exit (0);
    temp->content = ft_strdup(str);
    if (!temp->content)
        exit (0);
    if (!mini->var)
        mini->var = temp;
    else if (mini->var)
    {
        while (index->next)
            index = index->next;
        index->next = temp;
    }
}

void    get_prompt(t_mini *mini)
{
    char    *str;

    mini->prompt = mini_getenv(mini, "USER");
    mini->prompt = ft_strjoin(mini->prompt, "@minishell ~");
    str = ft_strnstr2(mini_getenv(mini, "PWD"), mini_getenv(mini, "USER"), 1000);
    if (str)
        mini->prompt = ft_strjoin(mini->prompt, str);
    else
        mini->prompt = ft_strjoin(mini->prompt, mini_getenv(mini, "PWD"));
    mini->prompt = ft_strjoin(mini->prompt, " $ ");
}

t_mini  *mini_init(char **env)
{
    t_mini  *mini;
    int     i;

    i = 0;
    mini = malloc (sizeof(t_mini));
    if (!mini)
        return (0);
	mini->cmd = NULL;
    while (env && env[i])
        get_var(mini, env[i++]);
    mini->env_size = i;
    mini->pid = getpid();
    get_prompt(mini);
    return (mini);
}

int	main(int argc, char **argv, char **env)
{
    t_mini	*mini;

	mini = mini_init(env);
	while (argc && argv[0])
    {
		signal(SIGQUIT, SIG_IGN);
		// signal(SIGINT, mini_new_line);
		get_cmd(mini, readline(mini->prompt));
		execute(mini);
    }
}
