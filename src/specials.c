/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specials.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:36:27 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/22 15:33:47 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

void	outfiles(t_mini *mini, char **cmds, int i, int j)
{
	char	*file;

	while (cmds[i])
	{
		if (cmds[i][j] == '>')
		{
			j++;
			if (cmds[i][j] == '>')
				j++;
			if (cmds[i][j])
			{
				file = manage_string(mini, &cmds[i][j], 0);
				open(file, O_CREAT | O_RDWR, 0777);
			}
			else if (cmds[i + 1] && cmds[i + 1][0] != '<'
					&& cmds[i + 1][0] != '>')
			{
				file = manage_string(mini, cmds[i + 1], 0);
				open(file, O_CREAT | O_RDWR, 0777);
			}
			g_status = 0;
			free (file);
		}
		i++;
	}
}
