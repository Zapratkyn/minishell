/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:25:41 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/25 16:07:25 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

void	get_path(t_mini *mini, t_cmd *cmd, char *path, int i)
{
	char	*exec;
	char	**paths;

	paths = NULL;
	exec = get_exec(mini, cmd, NULL, 0);
	if (exec)
	{
		paths = ft_split_paths(mini, mini_getenv(mini, "PATH"), ':');
		if (!access(exec, X_OK))
			cmd->path = ft_strdup(mini, exec);
		while (paths[i] && !cmd->path)
		{
			path = ft_insert(mini, paths[i++], '/', exec);
			if (!access(path, X_OK))
				cmd->path = ft_strdup(mini, path);
			free (path);
		}
		ft_free_tab(paths, ft_tablen(paths));
		if (!cmd->path && ft_strcmp(exec, "export") && ft_strcmp(exec, "unset")
			&& ft_strcmp(exec, "exit"))
			get_infos_error(mini, cmd, 3, exec);
		free (exec);
	}
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

void	set_outfile(t_mini *mini, t_cmd *cmd, int j, char *outfile)
{
	char	*file;

	file = manage_string(mini, outfile, 0);
	if (j == 1)
		cmd->outfile = open(file, O_CREAT | O_RDWR | O_TRUNC, 0777);
	else if (j == 2)
		cmd->outfile = open(file, O_CREAT | O_RDWR | O_APPEND, 0777);
	free (file);
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
		set_outfile(mini, cmd, j, outfile);
}
