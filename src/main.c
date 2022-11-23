/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:24:11 by gponcele          #+#    #+#             */
/*   Updated: 2022/11/23 14:58:37 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

void    get_prompt(t_mini mini)
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

t_mini  mini_init(char **env)
{
    t_mini  mini;

	mini.cmd = NULL;
    mini.env = env;
    mini.g_status = 0;
    mini.pid = getpid();
    return (mini);
}

int	main(int argc, char **argv, char **env)
{
    t_mini	mini;

	mini = mini_init(env);
	get_prompt(mini);
	while (argc && argv[0])
    {
		signal(SIGQUIT, SIG_IGN);
		// signal(SIGINT, mini_new_line);
		mini_parser(mini, mini.cmd, readline(" "));
    }
}
