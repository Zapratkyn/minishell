/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 11:05:17 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/30 13:04:56 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minish.h"

char	*ft_rev_strchr(char *str, char c)
{
	int	i;

	i = -1;
	while (str && str[++i])
		if (str[i] == c)
			return (ft_substr(str, 0, i));
	return (NULL);
}

int	is_env(t_mini *mini, char *s)
{
	t_var	*var;
	int		i;

	var = mini->var;
	while (var)
	{
		i = -1;
		while (var->content[++i])
			if (var->content[i] == '=')
				break ;
		if (!ft_strncmp(var->content, s, i))
			return (1);
		var = var->next;
	}
	return (0);
}

char	*remove_s_qu(char *s)
{
	char	*tmp1;
	char	*tmp2;
	char	**split;
	int		i;

	if ((!ft_strchr(s, S_QUOTE) && !ft_strchr(s, D_QUOTE))
		|| !ft_strchr(s, '='))
		return (NULL);
	tmp1 = ft_strchr(s, '=') + 1;
	split = ft_split(tmp1, S_QUOTE);
	tmp1 = ft_strdup(split[0]);
	i = 0;
	while (split[++i])
		tmp1 = ft_strjoin(tmp1, split[i]);
	i = -1;
	ft_free_tab(split);
	tmp2 = ft_strjoin(ft_substr(s, 0, ft_find_index(s, '=')), "=");
	tmp1 = ft_strjoin(tmp2, tmp1);
	free(tmp2);
	return (tmp1);
}

char	*remove_d_qu(char *s)
{
	char	*tmp1;
	char	*tmp2;
	char	**split;
	int		i;

	if ((!ft_strchr(s, D_QUOTE)))
		return (NULL);
	tmp1 = ft_strchr(s, '=') + 1;
	split = ft_split(tmp1, D_QUOTE);
	tmp1 = ft_strdup(split[0]);
	i = 0;
	while (split[++i])
		tmp1 = ft_strjoin(tmp1, split[i]);
	i = -1;
	ft_free_tab(split);
	tmp2 = ft_strjoin(ft_substr(s, 0, ft_find_index(s, '=')), "=");
	tmp1 = ft_strjoin(tmp2, tmp1);
	free(tmp2);
	return (tmp1);
}

void	remove_quotes(t_cmd *cmd, int index, char *s)
{
	char	*s1;
	char	*s2;

	s1 = remove_s_qu(s);
	s2 = NULL;
	if (s1)
		s2 = remove_d_qu(s1);
	if (s1 && !s2)
		cmd->cmds[index] = ft_strdup(s1);
	else if (s1 && s2)
		cmd->cmds[index] = ft_strdup(s2);
	if (s1)
		free(s1);
	if (s2)
		free(s2);
}
