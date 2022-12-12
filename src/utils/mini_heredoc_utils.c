/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_heredoc_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 12:53:53 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/12 12:58:57 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

int	end_of_heredoc(char *input, char *eof)
{
	if (!ft_strncmp(input, eof, ft_strlen(input))
		&& (ft_strlen(input) == ft_strlen(eof)))
		return (1);
	return (0);
}

char	*get_vars(t_mini *mini, char *str, int i)
{
	char	*result;

	result = ft_strdup(mini, "");
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			i++;
			result = ft_var(mini, &str[i], result);
			while (ft_isalnum(str[i]) || str[i] == '_')
				i++;
		}
		else
			result = ft_strjoin2(mini, result, str[i++]);
	}
	free (str);
	return (result);
}

int	eof_to_fd(t_mini *mini, char *str, int fd, char *file)
{
	str = manage_string(mini, str, 0);
	write (fd, str, ft_strlen(str));
	write (fd, "\n", 1);
	free (str);
	close (fd);
	fd = open(file, O_RDONLY);
	return (fd);
}
