/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:13:44 by ademurge          #+#    #+#             */
/*   Updated: 2022/12/13 17:07:20 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minish.h"

void	pipe_and_fork(t_mini *mini, t_cmd *cmd)
{
	if (pipe(cmd->fd) == -1)
		ft_error(mini, PIPE_ERR, EXIT);
	if (n_of_cmd(cmd) == 1 && par_builtin(mini, cmd))
		do_builtin(mini, cmd);
	cmd->pid = fork();
	if (cmd->pid == -1)
		ft_error(mini, FORK_ERR, EXIT);
	else if (cmd->pid == CHILD_PROC)
		exec_child(mini, cmd);
	wait(&g_status);
	if (WIFEXITED(g_status))
		g_status = WEXITSTATUS(g_status);
	else if (WIFSIGNALED(g_status))
	{
		g_status = WTERMSIG(g_status);
		if (g_status != 1)
			g_status -= 1;
	}
}

int	check_cmd(t_mini *mini, t_cmd *cmd)
{
	if (cmd->infile == -1 || cmd->outfile == -1)
	{
		g_status = 1;
		return (0);
	}
	if (!ch_builtin(mini, cmd) && !par_builtin(mini, cmd)
		&& !ft_strcmp(cmd->path, "none"))
	{
		g_status = 127;
		return (0);
	}
	if (ch_builtin(mini, cmd) && !check_builtin(mini, cmd))
	{
		g_status = 1;
		return (0);
	}
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

// char	*clean_string(t_mini *mini, char *str, int len, int i)
// {
// 	char	*result;
// 	int		j;

// 	j = 0;
// 	while (str[++i])
// 	{
// 		if (str[i] != S_QUOTE && str[i] != '"')
// 			len++;
// 	}
// 	result = malloc (sizeof(char) * len + 1);
// 	if (!result)
// 		ft_error(mini, MALLOC_ERR, EXIT);
// 	i = -1;
// 	while (str[++i])
// 	{
// 		if (str[i] != S_QUOTE && str[i] != '"')
// 			result[j++] = str[i];
// 	}
// 	result[j] = '\0';
// 	free (str);
// 	return (result);
// }
