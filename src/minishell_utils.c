/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:24:11 by gponcele          #+#    #+#             */
/*   Updated: 2022/11/24 10:26:21 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

char    *mini_getenv(t_mini *mini, char *var)
{
    int		i;
    int     len;

    len = ft_strlen(var);
	i = 0;
    while (ft_strncmp(mini->env[i], var, len) || mini->env[i][len] != '=')
        i++;
    if (!mini->env[i])
        return (NULL);
    return (&mini->env[i][len + 1]);
}

void    mini_exit(int sig)
{
	(void)sig;
    write (1, "exit\n", 5);
    exit(0);
}

// char    *ft_varname(char *str)
// {
//     char    result[10000];
//     int     i;
//     int     j;

//     i = 0;
//     j = 0;
//     while (str[i])
//     {
//         if (str[i] == 92)
//             i++;
//         result[j++] = str[i++];
//     }
//     return (ft_strdup(result));
// }

int	ft_quotes(char *str)
{
	int	i;
	int	quotes;
	int	double_quotes;

	i = 0;
	quotes = 0;
	double_quotes = 0;
	while (str[i] && str[i] != 124)
	{
		if (str[i] == '"')
			double_quotes++;
		else if (str[i] == 39)
			quotes++;
		i++;
	}
	if ((quotes % 2) != 0 || (double_quotes % 2) != 0)
		return (0);
	return (1);
}
