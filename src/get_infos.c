/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:25:41 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/06 16:38:46 by ademurge         ###   ########.fr       */
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
		exec = ft_strdup(mini, cmd->cmds[i]);
	if (ft_strchr(exec, S_QUOTE) || ft_strchr(exec, '"'))
		exec = clean_string(exec, 0, -1, 0);
	return (exec);
}

void	get_path(t_mini *mini, t_cmd *cmd, int i)
{
	char	*exec;
	char	*path;
	char	**paths;
	char	*temp;

	exec = NULL;
	exec = get_exec(mini, cmd);
	if (exec)
	{
		paths = ft_split(mini, mini_getenv(mini, "PATH"), ':');
		while (paths[i] && !cmd->path)
		{
			temp = ft_strdup(mini, paths[i++]);
			path = ft_strjoin2(mini, temp, '/');
			path = ft_strjoin(mini, path, exec);
			if (!access(path, F_OK))
				cmd->path = ft_strdup(mini, path);
			free (path);
		}
		if (!ch_builtin(mini, cmd) && !par_builtin(mini, cmd) && !cmd->path)
			get_infos_error(mini, 3, exec);
		free (exec);
		ft_free_tab(paths, i);
	}
	if (cmd->path || cmd->cmds[0][0] == '>' || cmd->cmds[0][0] == '<')
		get_infile(mini, cmd, ft_tablen(cmd->cmds));
}

int	get_infos_error(t_mini *mini, int i, char *s)
{
	char	*str;

	str = NULL;
	if (i == 1)
	{
		ft_error(mini, "syntax error near unexpected token `newline'", NO_EXIT);
		g_status = 258;
	}
	else if (i == 2)
	{
		str = ft_strjoin(mini, ft_strdup(mini, "3: cannot open "), s);
		str = ft_strjoin(mini, str, ": No such file or directory");
		ft_error(mini, str, NO_EXIT);
		free (str);
		g_status = 1;
	}
	else if (i == 3)
	{
		str = ft_strjoin(mini, ft_strdup(mini, s), " : command not found");
		ft_error(mini, str, NO_EXIT);
		free (str);
		g_status = 127;
	}
	return (-1);
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
			else if (!cmd->cmds[i][1] && cmd->cmds[i + 1])
				infile = ft_strdup(mini, cmd->cmds[i + 1]);
			else
				cmd->infile = get_infos_error(mini, 1, NULL);
		}
	}
	if (infile)
	{
		if (!access(infile, F_OK))
			cmd->infile = open(infile, O_RDONLY);
		else
			cmd->infile = get_infos_error(mini, 2, infile);
		free (infile);
	}
	if (cmd->infile != -1)
		get_outfile(mini, cmd, ft_tablen(cmd->cmds), 1);
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
			if (cmd->cmds[i][j])
				outfile = ft_strdup(mini, &cmd->cmds[i][j]);
			else if (!cmd->cmds[i][j] && cmd->cmds[i + 1])
				outfile = ft_strdup(mini, cmd->cmds[i + 1]);
			else
				cmd->outfile = get_infos_error(mini, 1, NULL);
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
