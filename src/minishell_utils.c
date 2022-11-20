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

char    *mini_getenv(t_mini *mini, char *var)
{
    t_var   *temp;
    int     len;
    char    *result;

    len = ft_strlen(var);
    temp = mini->var;
    while (ft_strncmp(temp->content, var, len) || temp->content[len] != '=')
        temp = temp->next;
    result = &temp->content[len + 1];
    return (result);
}

void    mini_exit(int sig, siginfo_t *info, t_mini *mini)
{
    (void)sig;
    (void)info;
    if (mini->cmd)
        ft_free_cmd(mini->cmd);
    ft_free_env(mini->var);
    free (mini->prompt);
    free (mini);
    write (1, "exit\n", 5);
    exit(EXIT_SUCCESS);
}
