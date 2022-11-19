/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:24:11 by gponcele          #+#    #+#             */
/*   Updated: 2022/11/15 11:35:38 by gponcele         ###   ########.fr       */
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
    temp->custom = 0;
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

void    get_prompt(t_mini *mini, char **env)
{
    char    *str;

    (void)env;
    mini->prompt = getenv("USER");
    mini->prompt = ft_strjoin(mini->prompt, "@minishell ~");
    str = ft_strnstr2(getenv("PWD"), getenv("USER"), 1000);
    mini->prompt = ft_strjoin(mini->prompt, str);
    mini->prompt = ft_strjoin(mini->prompt, " $ ");
}

t_mini  *mini_init(char **env)
{
    t_mini  *mini;
    int     i;

    i = 0;
    mini = malloc (sizeof(t_mini));
    mini->cmd = malloc (sizeof(t_cmd));
    if (!mini || !mini->cmd)
        return (0);
    while (env && env[i])
        get_var(mini, env[i++]);
    get_prompt(mini, env);
    return (mini);
}

int	main(int argc, char **argv, char **env)
{
    t_mini  *mini;

    mini = mini_init(env);
	while (argc && argv[0])
    {
        mini->cmd->full_path = readline(mini->prompt);
        if (!strncmp(mini->cmd->full_path, "env", 3) && ft_strlen(mini->cmd->full_path) == 3)
            mini_env(mini);
    }
}
