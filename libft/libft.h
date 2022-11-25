/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 18:07:27 by gponcele          #+#    #+#             */
/*   Updated: 2022/11/25 17:35:36 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>

# define MALLOC_ERR "Error in the memory allocation of a malloc."
# define NO_EXIT 0
# define EXIT 1

typedef struct s_var	t_var;

struct s_var
{
	char	*content;
	t_var	*next;
};

void					ft_error(char *type, int is_exit);
char					*ft_calloc(int count, int size);
char					*ft_insert(char *s1, char c, char *s2);
int						ft_isalnum(int c);
void					ft_lstadd_back(t_var **var, t_var *new);
void					ft_lstclear(t_var **var);
void					ft_lstdelone(t_var *var);
t_var					*ft_lstnew(char *content);
t_var					*ft_lstlast(t_var *var);
void					ft_putstr_fd(char *s, int fd);
char					**ft_split(char const *s, char c);
char					*ft_strchr(const char *s, int c);
int						ft_strcmp(char *s1, char *s2);
char					*ft_strdup(char *str);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_strjoin2(char *str, char c);
size_t					ft_strlcpy(char *dest, const char *src, size_t size);
size_t					ft_strlen(const char *s);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
char					*ft_strnstr(const char *haystack, const char *needle,
							size_t len);
char					*ft_strnstr2(const char *haystack, const char *needle,
							size_t len);
char					*ft_substr(char const *s, unsigned int start,
							size_t len);
void					ft_usleep(int count);

#endif