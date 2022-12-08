/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:25:41 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/07 17:01:42 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

char	*get_exec(t_mini *mini, t_cmd *cmd)
{
	char	*exec;
	int		i;

	i = 0;
	exec = NULL;
	while (cmd->cmds[i] && (cmd->cmds[i][0] == '<' || cmd->cmds[i][0] == '>'
		|| (i > 0 && cmd->cmds[i - 1][0] == '<' && !cmd->cmds[i - 1][1])
		|| (i > 0 && cmd->cmds[i - 1][0] == '>' && !cmd->cmds[i - 1][1])))
		i++;
	if (cmd->cmds[i])
	{
		exec = ft_strdup(cmd->cmds[i]);
		exec = manage_string(mini, exec);
	}
	return (exec);
}

void	get_path(t_mini *mini, t_cmd *cmd, int i)
{
	char	*exec;
	char	*path;

	exec = get_exec(mini, cmd);
	if (exec)
	{
		if (!access(exec, F_OK))
			cmd->path = exec;
		while (mini->paths[i] && !cmd->path)
		{
			path = ft_strjoin(ft_strdup(""), mini->paths[i++]);
			path = ft_strjoin2(path, '/');
			path = ft_strjoin(path, exec);
			if (!access(path, F_OK))
				cmd->path = ft_strdup(path);
			free (path);
		}
		if (!ch_builtin(cmd) && !par_builtin(cmd) && !cmd->path)
			get_infos_error(cmd, 3, exec);
		free (exec);
	}
	else
		cmd->path = ft_strdup("none");
	if (ft_strncmp(cmd->path, "none", 4))
		get_infile(mini, cmd, ft_tablen(cmd->cmds));
}

void	set_infile(t_mini *mini, t_cmd *cmd, char *infile)
{
	infile = manage_string(mini, infile);
	if (!access(infile, F_OK))
		cmd->infile = open(infile, O_RDONLY);
	else
		cmd->infile = get_infos_error(cmd, 2, infile);
	free (infile);
}

void	get_infile(t_mini *mini, t_cmd *cmd, int i)
{
	char	*infile;

	infile = NULL;
	while (cmd->cmds[--i] && i >= 0 && !infile && cmd->infile == STDIN_FILENO)
	{
		if (cmd->cmds[i][0] == '<')
		{
			if (cmd->cmds[i][1] && cmd->cmds[i][1] != '<')
				infile = ft_strdup(&cmd->cmds[i][1]);
			else if (!cmd->cmds[i][1] && cmd->cmds[i + 1] && cmd->cmds[i + 1][0] != '<' && cmd->cmds[i + 1][0] != '>')
				infile = ft_strdup(cmd->cmds[i + 1]);
			else
				cmd->infile = get_infos_error(cmd, 1, NULL);
		}
	}
	if (infile)
		set_infile(mini, cmd, infile);
	if (cmd->infile != -1)
		get_outfile(cmd, ft_tablen(cmd->cmds), 1);
}

void	get_outfile(t_cmd *cmd, int i, int j)
{
	char	*outfile;

	outfile = NULL;
	while (cmd->cmds[--i] && !outfile && i >= 0)
	{
		if (cmd->cmds[i][0] == '>')
		{
			if (cmd->cmds[i][1] == '>')
				j++;
			if (cmd->cmds[i][j])
				outfile = ft_strdup(&cmd->cmds[i][j]);
			else if (!cmd->cmds[i][j] && cmd->cmds[i + 1] && cmd->cmds[i + 1][0] != '<' && cmd->cmds[i + 1][0] != '>')
				outfile = ft_strdup(cmd->cmds[i + 1]);
			else
				cmd->outfile = get_infos_error(cmd, 1, NULL);
		}
	}
	if (outfile)
	{
		if (j == 1)
			cmd->outfile = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0777);
		else if (j == 2)
			cmd->outfile = open(outfile, O_CREAT | O_RDWR | O_APPEND, 0777);
		free (outfile);
	}
}
