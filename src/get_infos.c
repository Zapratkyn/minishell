/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:25:41 by gponcele          #+#    #+#             */
/*   Updated: 2022/11/23 18:37:01 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

char    *get_exec(t_cmd *cmd)
{
    char    *exec;
    int     i;

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

void    get_path(t_mini *mini, t_cmd *cmd, int i)
{
    char    *exec;
    char    *path;
    char    **paths;

    exec = NULL;
    exec = get_exec(cmd);
    cmd->pid = -1;
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
        if (!cmd->path && exec[1])
            printf("%s : invalid command\n", exec);
        free (exec);
        ft_free_paths(paths);
    }
    get_infile(cmd, -1);
}

int infile_error(int i, char *infile)
{
    if (i == 1)
        printf("2: Syntax error: newline unexpected\n");
    else if (i == 2)
        printf("3: cannot open %s: No such file\n", infile);
    return (-1);
}

void    get_infile(t_cmd *cmd, int i)
{
    char    *infile;

    infile = NULL;
    cmd->infile = 0;
    if (cmd->cmds[0][0] == '<' && !cmd->cmds[0][1] && !cmd->cmds[1])
        cmd->infile = infile_error(1, NULL);
    while (cmd->cmds[++i] && !infile)
    {
        if (cmd->cmds[i][0] == '<' && cmd->cmds[i][1] && cmd->cmds[i][1] != '<')
            infile = ft_strdup(&cmd->cmds[i][1]);
        else if (cmd->cmds[i][0] == '<' && !cmd->cmds[i][1] && cmd->cmds[i + 1])
            infile = ft_strdup(cmd->cmds[i + 1]);
    }
    if (infile)
    {
        if (!access(infile, F_OK))
            cmd->infile = open(infile, O_RDONLY);
        else
            cmd->infile = infile_error(2, infile);
        free (infile);
    }
    get_outfile(cmd, 0);
}

void    get_outfile(t_cmd *cmd, int i)
{
    char    *outfile;

    outfile = NULL;
    cmd->outfile = 1;
    if (cmd->cmds[0][0] == '>' && !cmd->cmds[0][1] && !cmd->cmds[1])
    {
        printf("2: Syntax error: newline unexpected");
        cmd->outfile = -1;
    }
    while (cmd->cmds[i] && !outfile)
    {
        if (cmd->cmds[i][0] == '>' && cmd->cmds[i][1] && cmd->cmds[i][1] != '>')
            outfile = ft_strdup(&cmd->cmds[i][1]);
        else if (cmd->cmds[i][0] == '>' && !cmd->cmds[i][1] && cmd->cmds[i + 1])
            outfile = ft_strdup(cmd->cmds[i + 1]);
        i++;
    }
    if (outfile)
    {
        cmd->outfile = open(outfile, O_CREAT|O_RDONLY, 0777);
        free (outfile);
    }
}