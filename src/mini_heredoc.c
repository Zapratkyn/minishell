/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 15:09:46 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/08 11:59:10 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

char	*get_eof(char *str, char *eof)
{
	int		i;
	char	c;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i])
		eof = ft_strdup("");
	while (str[i] && str[i] != ' ')
	{
		if (str[i] == S_QUOTE || str[i] == '"')
		{
			c = str[i++];
			while (str[i] != c)
				i++;
			i++;
		}
		else
			eof = ft_strjoin2(eof, str[i++]);
	}
	return (eof);
}

// int	check_input(char *str, char *end)
// {
// 	if (!str)
// 		return (-1);
// 	else if ((!ft_strncmp(str, end, ft_strlen(end))
// 			&& ft_strlen(str) == ft_strlen(end)))
// 		return (-2);
// 	return (1);
// }

// int	get_input(char *str, char *end, int fd)
// {
// 	char	*input;
// 	int		check;

// 	g_status = 0;
// 	check = 0;
// 	input = ft_calloc(1, 1);
// 	fd = add_heredoc("/tmp/mini_heredocs/heredoc_");
// 	end = get_end(str, "");
// 	while (1)
// 	{
// 		signal(SIGINT, mini_new_line);
// 		signal(SIGQUIT, SIG_IGN);
// 		input = (readline("> "));
// 		check = check_input(input, end);
// 		if (check < 0 || g_status == 1)
// 			break ;
// 		write (fd, input, ft_strlen(input));
// 		write (fd, "\n", 1);
// 		free (input);
// 	}
// 	if (g_status == 1 || check == -1 || !end)
// 		return (0);
// 	return (fd);
// }

char	*get_vars(t_mini *mini, char *str, int i)
{
	char	*result;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '"' && str[i + 1] != ' ')
		{
			i++;
			result = ft_var(mini, &str[i], result);
			while (ft_isalnum(str[i]) || str[i] == '_')
				i++;
		}
		else
			result = ft_strjoin2(result, str[i++]);
	}
	free (str);
	return (result);
}

char	*manage_line(t_mini *mini, char *str, char *eof)
{
	if (!ft_strchr(eof, '"') && !ft_strchr(eof, S_QUOTE))
	{
		str = get_vars(mini, str, 0);
		return (str);
	}
	else if ((ft_strchr(eof, '"') || ft_strchr(eof, S_QUOTE)) && ft_quotes(eof, -1, 0, 0))
		return (str);
	return (0);
}

int	fill_fd(t_mini *mini, char *input, int fd, char *eof)
{
	if (!input)
		return (0);
	else if (!strncmp(input, eof, ft_strlen(input)) && (ft_strlen(input) == ft_strlen(eof)))
	{
		free (input);
		return (0);
	}
	else
	{
		input = manage_line(mini, input, eof);
		write (fd, input, ft_strlen(input));
		write (fd, "\n", 1);
		free (input);
		return (1);
	}
}

int	add_heredoc(t_mini *mini)
{
	int		i;
	int		fd;
	char	*nb;
	char	*file;

	(void)mini;
	i = 1;
	nb = ft_itoa(i);
	file = ft_strjoin(ft_strdup("/tmp/heredoc_"), nb);
	free (nb);
	while (!access(file, F_OK))
	{
		i++;
		free (file);
		nb = ft_itoa(i);
		file = ft_strjoin(ft_strdup("/tmp/heredoc_"), nb);
		free (nb);
	}
	fd = open(file, O_CREAT | O_RDWR, 0777);
	free (file);
	return (fd);
}

int	add_fd(t_mini *mini, char *eof)
{
	int	fd;
	
	fd = add_heredoc(mini);
	while (1)
	{
		signal(SIGINT, mini_new_line);
		signal(SIGQUIT, SIG_IGN);
		if (!fill_fd(mini, readline("> "), fd, eof))
			break ;
	}
	return (fd);
}

int	mini_heredoc(t_mini *mini, t_cmd *cmd, int fd, int i)
{
	char	*eof;
	
	while (cmd->cmds[i])
	{
		if (cmd->cmds[i][0] == '<')
		{
			fd = STDIN_FILENO;
			if (cmd->cmds[i][1] == '<')
			{
				if (cmd->cmds[i][2])
					eof = &cmd->cmds[i][2];
				else if (!cmd->cmds[i][2] && cmd->cmds[i + 1] && cmd->cmds[i + 1] != '<' && cmd->cmds[i + 1][0] != '>')
					eof = cmd->cmds[i + 1];
				else
					return (get_infos_error(cmd, 1, NULL));
				fd = add_fd(mini, eof);
				if (fd == -1)
					return (-1);
			}
		}
		i++;
	}
	return (fd);
}
