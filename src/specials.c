/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specials.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:36:27 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/23 21:57:27 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

void	outfiles(t_mini *mini, char **cmds, int i, int j)
{
	char	*file;

	file = NULL;
	while (cmds[i])
	{
		if (cmds[i][j] == '>')
		{
			j++;
			if (cmds[i][j] == '>')
				j++;
			if (cmds[i][j] && cmds[i][j] != '>' && cmds[i][j] != '<')
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
			free (file);
		}
		i++;
	}
}
