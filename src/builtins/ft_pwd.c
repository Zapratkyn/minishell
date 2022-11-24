/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 10:52:09 by ademurge          #+#    #+#             */
/*   Updated: 2022/11/24 13:39:58 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minish.h"

void	update_pwd(t_mini *mini, char *type)
{
	t_list	*lst;
	char	*tmp;

	lst = mini->l_env;
	tmp = NULL;
	while (lst)
	{
		if (!ft_strncmp(lst->data, type, ft_strlen(type)))
		{
			tmp = getcwd(tmp, 0);
			if (!tmp)
				ft_error(PWD_ERR);
			free(lst->data);
			lst->data = ft_strjoin(type, tmp);
			free(tmp);
		}
		lst = lst->next;
	}
}

void	ft_pwd(t_cmd *cmd)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (!pwd)
		ft_error(PWD_ERR);
	ft_putstr_fd(pwd, cmd->outfile);
	write(cmd->outfile, "\n", 1);
	free(pwd);
}