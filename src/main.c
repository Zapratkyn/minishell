/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:24:11 by gponcele          #+#    #+#             */
/*   Updated: 2022/11/23 18:29:18 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

void    get_var(t_mini *mini, char *str)
{
    t_var   	*index;
    t_var   	*temp;
	static int	i = 0;
	
    index = mini->var;
    temp = malloc (sizeof(t_var));
    if (!temp)
        exit (0);
    temp->content = ft_strdup(str);
    if (!temp->content)
        exit (0);
    if (i == 0)
	{
        mini->var = temp;
		i++;
	}
    else if (i == 1)
    {
        while (index->next)
            index = index->next;
        index->next = temp;
    }
}

char	*get_prompt(t_mini *mini)
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
    prompt = ft_strjoin(prompt, " % ");
	return (prompt);
}

t_mini  mini_init(char **env)
{
    t_mini  mini;
	int		i;

	i = 0;
	mini.cmd = NULL;
    mini.env = env;
	while (env && env[i])
        get_var(&mini, env[i++]);
    mini.g_status = 0;
    mini.pid = getpid();
	mini.prompt = get_prompt(&mini);
    return (mini);
}

int    mini_parser(t_mini *mini, char *str)
{
	if (!str)
		return (0);
	if (is_input(str))
	{
		if (str[0] != ' ')
			add_history(str);
    	mini->cmd = get_cmd(mini, mini->cmd, str, 0);
	}
	if (mini->cmd->path)
		printf("%s\n", mini->cmd->path);
    // if (mini->cmd)
    // {
	//     if (mini->cmd->path)
	//     	printf("path : %s\n", mini->cmd->path);
	//     printf("infile : %d\n", mini->cmd->infile);
	//     printf("outfile : %d\n", mini->cmd->outfile);
    // }
	// if (!ft_strncmp(mini->cmd->full_cmd[0], "echo", 4) && mini->cmd->full_cmd[1])
	// 	printf("%s\n", mini->cmd->full_cmd[1]);	
	// exec(mini);
	free (str);
	// ft_free_cmd(mini->cmd);
	get_prompt(mini);
	return (1);
}

void	mini_new_line(int sig)
{
	(void)sig;
	write (1, "\n", 1);
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
			break;
    }
	ft_quit(&mini);
}
