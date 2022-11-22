/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:25:41 by gponcele          #+#    #+#             */
/*   Updated: 2022/11/21 17:40:15 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minish.h"

char	*delete_quotes(char *str)
{
	char	*result;
	int		i;
	int		j;

	i = 1;
	j = 0;
	result = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	while (str[i] != 39 && str[i] != '"')
	{
		result[j] = str[i];
		i++;
		j++;
	}
	free (str);
	return (result);
}

// char	*ft_var(char *str)
// {
// 	int		i;
// 	int		j;
// 	int		len;
// 	char	*result;

// 	i = 1;
// 	j = 0;
// 	len = 0;
// 	while (str[i] != '"' && str[i] != ' ')
// 	{
// 		len++;
// 		i++;
// 	}
// 	result = malloc (sizeof(char) * len + 1);
// 	if (!result)
// 		return (NULL);
// 	i = 1;
// 	while (str[i] != '"' && str[i] != ' ')
// 		result[j++] = str[i++];
// 	result[i] = '\0';
// 	return (result);
// }

// char	*delete_double_quotes(t_mini *mini, char *str, int i)
// {
// 	char	*result;
// 	char	*index;
// 	char	*var;
	
	
// 	result = malloc(sizeof(char) * 2);
// 	if (!result)
// 		return (NULL);
// 	result[0] = '"';
// 	result[1] = '\0';
// 	index = &str[1];
// 	while (index[i] != '"')
// 	{
// 		if (index[i] == '$')
// 		{
// 			var = ft_var(&index[i]);
// 			printf("%s\n", var);
// 			result = ft_strjoin(result, mini_getenv(mini, var));
// 			i += ft_strlen(var);
// 			write (1, "OK\n", 3);
// 			free (var);
// 		}
// 		else
// 			result = ft_strjoin2(result, index[i++]);
// 	}
// 	free (str);
// 	return (delete_quotes(result));
// }

char	*to_var(t_mini *mini, char *str)
{
	char	*result;

	result = ft_strdup(mini_getenv(mini, &str[1]));
	if (!result)
		return (NULL);
	free (str);
	return (result);
}

int	get_cmd(t_mini *mini, char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	mini->cmd = malloc (sizeof(t_cmd));
	if (!mini->cmd)
		return (0);
	mini->cmd->infile = 0;
	mini->cmd->outfile = 1;
	mini->cmd->full_cmd = ft_split_cmd(str, 0, 0);
	while (mini->cmd->full_cmd[i])
	{
		if (mini->cmd->full_cmd[i][0] == 39)
			mini->cmd->full_cmd[i] = delete_quotes(mini->cmd->full_cmd[i]);
		// if (mini->cmd->full_cmd[i][0] == '"')
		// 	mini->cmd->full_cmd[i] = delete_double_quotes(mini, mini->cmd->full_cmd[i], 0);
		else if (mini->cmd->full_cmd[i][0] == '$')
			mini->cmd->full_cmd[i] = to_var(mini, mini->cmd->full_cmd[i]);
		printf("%s\n", mini->cmd->full_cmd[i]);
		i++;
	}
	free (str);
	return (1);
}