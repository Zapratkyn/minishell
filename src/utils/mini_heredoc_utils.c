/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_heredoc_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 12:53:53 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/13 15:39:53 by gponcele         ###   ########.fr       */
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
	mini->tempstr2 = ft_strdup(mini, str);
	mini->tempstr2 = manage_string(mini, mini->tempstr2, 0);
	write (fd, mini->tempstr2, ft_strlen(mini->tempstr2));
	write (fd, "\n", 1);
	free (mini->tempstr2);
	mini->tempstr2 = NULL;
	close (fd);
	fd = open(file, O_RDONLY);
	free (file);
	file = NULL;
	return (fd);
}
