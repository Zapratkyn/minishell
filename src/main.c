/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:24:11 by gponcele          #+#    #+#             */
/*   Updated: 2022/11/24 16:01:28 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

void    get_prompt(t_mini *mini)
{
    char    *str;
	char	*prompt;

    prompt = ft_strdup(mini_getenv(mini, "USER"));
    prompt = ft_strjoin(prompt, "@minishell ");
    str = ft_strnstr2(mini_getenv(mini, "PWD"), mini_getenv(mini, "USER"), 1000);
    if (str)
	{
		prompt = ft_strjoin(prompt, "~");
        prompt = ft_strjoin(prompt, str);
	}
    else
        prompt = ft_strjoin(prompt, mini_getenv(mini, "PWD"));
    prompt = ft_strjoin(prompt, " %");
	printf("%s", prompt);
	free (prompt);
}

void	init_l_env(t_mini *mini)
{
	int	i;

	i = 0;
	mini->l_env = ft_lstnew(mini->env[i]);
	while (mini->env[++i])
		ft_lstadd_back(&mini->l_env, ft_lstnew(mini->env[i]));
}

void  mini_init(t_mini *mini, char **env)
{
	mini->cmd = NULL;
	mini->env = env;
	init_l_env(mini);
	mini->g_status = 0;
	mini->pid = getpid();
}

void    mini_parser(t_mini *mini, char *str)
{
	if (str)
	{
		add_history(str);
		mini->cmd = get_cmd(mini, mini->cmd, str, 0);
		execute(mini);
		//if (mini->cmd->path)
		//	printf("path : %s\n", mini->cmd->path);
	}
	// if (!ft_strncmp(mini->cmd->full_cmd[0], "echo", 4) && mini->cmd->full_cmd[1])
	// 	printf("%s\n", mini->cmd->full_cmd[1]);
	//
	free (str);
	// ft_free_cmd(mini->cmd);
	get_prompt(mini);
}

int	main(int argc, char **argv, char **env)
{
    t_mini	mini;

	mini_init(&mini, env);
	get_prompt(&mini);
	while (argc && argv[0])
	{
		//signal(SIGQUIT, SIG_IGN);
		// signal(SIGINT, mini_new_line);
		mini_parser(&mini, readline(" "));
	}
}
