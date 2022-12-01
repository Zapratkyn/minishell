/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:13:44 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/01 18:58:53 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minish.h"

void	pipe_and_fork(t_mini *mini, t_cmd *cmd)
{
	if (pipe(cmd->fd) == -1)
		ft_error(PIPE_ERR, EXIT);
	if (n_of_cmd(cmd) == 1 && par_builtin(cmd))
		do_builtin(mini, cmd);
	cmd->pid = fork();
	if (cmd->pid == -1)
		ft_error(FORK_ERR, EXIT);
	else if (cmd->pid == CHILD_PROC)
		exec_child(mini, cmd);
	waitpid(cmd->pid, NULL, 0);
}

int	check_cmd(t_cmd *cmd)
{
	if (cmd->infile == -1 || cmd->outfile == -1)
		return (0);
	if (!ch_builtin(cmd) && !par_builtin(cmd) && !cmd->path)
		return (0);
	return (1);
}

int	n_of_cmd(t_cmd *cmd)
{
	int		n;
	t_cmd	*tmp;

	n = 0;
	tmp = cmd;
	while (tmp)
	{
		n++;
		tmp = tmp->next;
	}
	return (n);
}

char	*clean_string(char *str)
{
	int		i;
	char	*result;
	char	c;

	i = -1;
	result = calloc (1, 1);
	if (!result)
		return (NULL);
	while (str[++i])
	{
		if (str[i] == S_QUOTE || str[i] == '"')
		{
			c = str[i++];
			while (str[i] != c)
				result = ft_strjoin2(result, str[i++]);
		}
		else
			result = ft_strjoin2(result, str[i]);
	}
	return (result);
}