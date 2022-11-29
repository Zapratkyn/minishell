/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:25:41 by gponcele          #+#    #+#             */
/*   Updated: 2022/11/29 16:57:40 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

char	*get_exec(t_cmd *cmd)
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
		exec = ft_strdup(cmd->cmds[i]);
	return (exec);
}

void	get_path(t_mini *mini, t_cmd *cmd, int i)
{
	char	*exec;
	char	*path;
	char	**paths;

	exec = NULL;
	exec = get_exec(cmd);
	if (exec)
	{
		paths = ft_split(mini_getenv(mini, "PATH"), ':');
		while (paths[i] && !cmd->path)
		{
			path = ft_strjoin2(paths[i++], '/');
			path = ft_strjoin(path, exec);
			if (!access(path, F_OK))
				cmd->path = ft_strdup(path);
			free (path);
		}
		if (!ch_builtin(cmd) && !par_builtin(cmd) && !cmd->path)
			get_infos_error(3, exec);
		free (exec);
		ft_free_paths(paths);
	}
	if (cmd->path || cmd->cmds[0][0] == '>' || cmd->cmds[0][0] == '<')
		get_infile(cmd, -1);
}

int	get_infos_error(int i, char *s)
{
	char	*str;

	str = NULL;
	if (i == 1)
	{
		ft_error("syntax error near unexpected token `newline'", 0);
		g_status = 258;
	}
	else if (i == 2)
	{
		str = ft_strjoin("3: cannot open ", s);
		str = ft_strjoin(str, ": No such file or directory");
		ft_error(str, 0);
		free (str);
		g_status = 1;
	}
	else if (i == 3)
	{
		str = ft_strjoin(s, " : command not found");
		ft_error(str, 0);
		free (str);
		g_status = 127;
	}
	return (-1);
}

void	get_infile(t_cmd *cmd, int i)
{
	char	*infile;

	infile = NULL;
	while (cmd->cmds[++i] && !infile)
	{
		if (cmd->cmds[i][0] == '<')
		{
			if (cmd->cmds[i][1] && cmd->cmds[i][1] != '<')
				infile = ft_strdup(&cmd->cmds[i][1]);
			else if (!cmd->cmds[i][1] && cmd->cmds[i + 1])
				infile = ft_strdup(cmd->cmds[i + 1]);
			else
				cmd->infile = get_infos_error(1, NULL);
		}
	}
	if (infile)
	{
		if (!access(infile, F_OK))
			cmd->infile = open(infile, O_RDONLY);
		else
			cmd->infile = get_infos_error(2, infile);
		free (infile);
	}
	if (cmd->infile != -1)
		get_outfile(cmd, -1, 1);
}

void	get_outfile(t_cmd *cmd, int i, int j)
{
	char	*outfile;

	outfile = NULL;
	while (cmd->cmds[++i] && !outfile)
	{
		if (cmd->cmds[i][0] == '>')
		{
			if (cmd->cmds[i][1] == '>')
				j++;
			if (cmd->cmds[i][j])
				outfile = ft_strdup(&cmd->cmds[i][j]);
			else if (!cmd->cmds[i][j] && cmd->cmds[i + 1])
				outfile = ft_strdup(cmd->cmds[i + 1]);
			else
				cmd->outfile = get_infos_error(1, NULL);
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
