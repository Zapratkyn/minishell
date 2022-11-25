/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 18:07:27 by gponcele          #+#    #+#             */
/*   Updated: 2022/11/25 15:32:56 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>

# define MALLOC_ERR "Error in the memory allocation of a malloc."

typedef struct s_list	t_list;
struct	s_list
{
	char	*data;
	t_list	*next;
};

void					ft_error(char *type);
char					*ft_calloc(int count, int size);
char					*ft_insert(char *s1, char c, char *s2);
int						ft_isalnum(int c);
void					ft_lstadd_back(t_list **lst, t_list *new);
void					ft_lstclear(t_list **lst);
void					ft_lstdelone(t_list *lst);
t_list					*ft_lstnew(char *data);
t_list					*ft_lstlast(t_list *lst);
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
char					*ft_strnstr(const char *haystack, const char *needle, size_t len);
char					*ft_strnstr2(const char *haystack, const char *needle, size_t len);
char					*ft_substr(char const *s, unsigned int start, size_t len);
void					ft_usleep(int count);

#endif