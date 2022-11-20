/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:53:43 by gponcele          #+#    #+#             */
/*   Updated: 2022/07/18 12:25:42 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

void    ft_free_env(t_var *var)
{
    if (var->next)
        ft_free_env(var->next);
    free (var);
}

void    ft_free_cmd(t_cmd *cmd)
{
    if (cmd->next)
        ft_free_cmd(cmd->next);
    free (cmd);
}
