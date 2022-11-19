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

void    mini_env(t_mini *mini)
{
    t_var   *temp;

    temp = mini->var;
    while (temp)
    {
        printf("%s\n", temp->content);
        temp = temp->next;
    }
}