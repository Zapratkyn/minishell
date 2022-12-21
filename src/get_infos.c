/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:25:41 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/21 11:23:06 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

void	get_path(t_mini *mini, t_cmd *cmd, char *path, int i)
{
	char	*exec;

	exec = get_exec(mini, cmd);
	if (exec)
	{
		if (!access(exec, X_OK))
			cmd->path = ft_strdup(mini, exec);
		while (mini->paths[i] && !cmd->path)
		{
			path = ft_strjoin(mini, ft_strdup(mini, ""), mini->paths[i++]);
			path = ft_strjoin2(mini, path, '/');
			path = ft_strjoin(mini, path, exec);
			if (!access(path, X_OK))
				cmd->path = ft_strdup(mini, path);
			free (path);
		}
		if ((!ch_builtin(cmd) && !par_builtin(cmd)
				&& !cmd->path))
			get_infos_error(mini, cmd, 3, exec);
		free (exec);
	}
	else
		cmd->path = ft_strdup(mini, "none");
	if (ft_strncmp(cmd->path, "none", 4))
		get_infile(mini, cmd, ft_tablen(cmd->cmds));
}

void	set_infile(t_mini *mini, t_cmd *cmd, char *infile)
{
	infile = manage_string(mini, infile, 1);
	if (!access(infile, F_OK))
		cmd->infile = open(infile, O_RDONLY);
	else
		cmd->infile = get_infos_error(mini, cmd, 2, infile);
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
				infile = ft_strdup(mini, &cmd->cmds[i][1]);
			else if (!cmd->cmds[i][1] && cmd->cmds[i + 1]
					&& cmd->cmds[i + 1][0] != '<' && cmd->cmds[i + 1][0] != '>')
				infile = ft_strdup(mini, cmd->cmds[i + 1]);
			else
				cmd->infile = get_infos_error(mini, cmd, 1, NULL);
		}
	}
	if (infile)
		set_infile(mini, cmd, infile);
	if (cmd->infile != -1)
		get_outfile(mini, cmd, ft_tablen(cmd->cmds), 1);
}

void	set_outfile(t_cmd *cmd, int j, char *outfile)
{
	if (j == 1)
		cmd->outfile = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0777);
	else if (j == 2)
		cmd->outfile = open(outfile, O_CREAT | O_RDWR | O_APPEND, 0777);
	free (outfile);
}

void	get_outfile(t_mini *mini, t_cmd *cmd, int i, int j)
{
	char	*outfile;

	outfile = NULL;
	while (cmd->cmds[--i] && !outfile && i >= 0)
	{
		if (cmd->cmds[i][0] == '>')
		{
			if (cmd->cmds[i][1] == '>')
				j++;
			if (cmd->cmds[i][j] && cmd->cmds[i][j] != '>'
				&& cmd->cmds[i][j] != '<')
				outfile = ft_strdup(mini, &cmd->cmds[i][j]);
			else if (!cmd->cmds[i][j] && cmd->cmds[i + 1]
					&& cmd->cmds[i + 1][0] != '<' && cmd->cmds[i + 1][0] != '>')
				outfile = ft_strdup(mini, cmd->cmds[i + 1]);
			else
				cmd->outfile = get_infos_error(mini, cmd, 1, NULL);
		}
	}
	if (outfile)
		set_outfile(cmd, j, outfile);
}
