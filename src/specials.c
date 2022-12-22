/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specials.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:36:27 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/22 11:33:35 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

void	outfiles(char **cmds, int i, int j)
{
	while (cmds[i])
	{
		if (cmds[i][j] == '>')
		{
			j++;
			if (cmds[i][j] == '>')
				j++;
			if (cmds[i][j])
			{
				open(&cmds[i][j], O_CREAT | O_RDWR, 0777);
				g_status = 0;
			}
			else if (cmds[i + 1] && cmds[i + 1][0] != '<' && cmds[i + 1][0] != '>')
			{
				open(cmds[i + 1], O_CREAT | O_RDWR, 0777);
				g_status = 0;
			}
		}
		i++;
	}
}

