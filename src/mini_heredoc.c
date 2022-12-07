/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 15:09:46 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/07 17:10:03 by gponcele         ###   ########.fr       */
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
	while (str[i] && str[i] != ' ')
	{
		eof = ft_strdup("");
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
			result = ft_strjoin(result, ft_var(mini, &str[i]));
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
	{
		read(fd, input, INT_MAX);
		printf("%s", input);
		free (input);
		return (0);
	}
	else if (!strncmp(input, eof, ft_strlen(input)) && (ft_strlen(input) == ft_strlen(eof)))
	{
		free (input);
		free (eof);
		eof = NULL;
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

int	manage_fd(t_mini *mini, int fd, char *eof)
{
	while (1)
	{
		signal(SIGINT, mini_new_line);
		signal(SIGQUIT, SIG_IGN);
		if (g_status == 1 || !fill_fd(mini, readline("> "), fd, eof))
			break ;
	}
	if (eof)
	{
		free (eof);
		return (-1);
	}
	return (fd);
}

int	add_heredoc(void)
{
	int		i;
	int		fd;
	char	*nb;
	char	*file;

	i = 1;
	nb = ft_itoa(i);
	file = ft_strjoin(ft_strdup("/tmp/mini_heredocs/heredoc_"), nb);
	free (nb);
	while (!access(file, F_OK))
	{
		i++;
		free (file);
		nb = ft_itoa(i);
		file = ft_strjoin(ft_strdup("/tmp/mini_heredocs/heredoc_"), nb);
		free (nb);
	}
	fd = open(file, O_CREAT | O_RDWR, 0777);
	free (file);
	return (fd);
}

int	mini_heredoc(t_mini *mini, char *str, int fd)
{
	char	*eof;
	int		i;

	i = 0;
	while (str[i])
	{
		if ((i == 0 && str[i] == '<') || (i > 0 && str[i - 1] == ' '))
		{
			fd = STDIN_FILENO;
			if (str[++i] == '<')
			{
				if (str[i + 1] == '<')
					return (-1);
				eof = get_eof(&str[i + 1], NULL);
				if (!eof)
					return (-1);
				fd = add_heredoc();
				fd = manage_fd(mini, fd, eof);
				if (fd == -1)
					return (fd);
			}
		}
		else
			i++;
	}
	return (fd);
}
