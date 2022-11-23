/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:24:11 by gponcele          #+#    #+#             */
/*   Updated: 2022/11/21 12:19:50 by gponcele         ###   ########.fr       */
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
    if (!temp)
        return (NULL);
    result = &temp->content[len + 1];
    return (result);
}

void    mini_exit(int sig)
{
	(void)sig;
    write (1, "exit\n", 5);
    exit(0);
}

char    *ft_varname(char *str)
{
    char    result[10000];
    int     i;
    int     j;

    i = 0;
    j = 0;
    while (str[i])
    {
        if (str[i] == 92)
            i++;
        result[j++] = str[i++];
    }
    return (ft_strdup(result));
}

void    mini_add_history(t_mini *mini, t_cmd *cmd, char *str)
{
    add_history(str);
    get_cmd(mini, cmd, str, 0);
}