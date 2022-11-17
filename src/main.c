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

void    get_var(t_prompt *prompt, char *str)
{
    t_list      *index;
    int         i;
    static int  k = 0;
    t_list      *temp;

    index = prompt->var;
    temp = malloc (sizeof(t_list));
    temp->content = malloc (sizeof(char) * ft_strlen(str) + 1);
    if (!temp->content || !temp)
        exit (0);
    i = 0;
    while (str[i])
    {
        temp->content[i] = str[i];
        i++;
    }
    temp->content[i] = '\0';
    if (index == 0)
        prompt->var = temp;
    else if (index != 0)
    {
        while (index->next)
            index = index->next;
        index->next = temp;
    }
    k++;
}

void    get_prompt(t_prompt *prompt)
{
    t_list  *temp;
    // char    s1[1000];
    // char    s2[1000];

    temp = prompt->var;
    while (temp)
    {
        if (ft_strncmp(temp->content, "USER=", 5))
        {
            
        }
    }
}

t_prompt  *prompt_init(char **env)
{
    t_prompt  *prompt;
    int       i;

    i = 0;
    prompt = malloc (sizeof(t_prompt));
    if (!prompt)
        return (0);
    prompt->cmd = NULL;
    while (env && env[i])
        get_var(prompt, env[i++]);
    get_prompt(prompt);
    return (prompt);
}

int	main(int argc, char **argv, char **env)
{
    t_prompt  *prompt;

    (void)argv;
    (void)prompt;
    prompt = prompt_init(env);
	while (argc)
    {

    }
}
