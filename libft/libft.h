/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 18:07:27 by gponcele          #+#    #+#             */
/*   Updated: 2022/12/02 10:28:45 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H

/*
** Libraries
*/

# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>

/*
** Define constants
*/

/* Characters */
# define NO_EXIT 0
# define EXIT 1

/* Error */
# define MALLOC_ERR "Error in the memory allocation of a malloc."

/*
** Structures
*/

/* Var structure */

typedef struct s_var	t_var;

struct s_var
{
	char	*content;
	t_var	*next;
	t_var	*prev;
};

/*
** Functinons
*/

/* Linked List */
int						ft_lst_index(t_var **l_var, t_var *var);
char					**ft_lst_to_str(t_var *var);
void					ft_lstadd_back(t_var **var, t_var *new);
void					ft_lstclear(t_var **var);
void					ft_lstdelone(t_var **l_var, int i);
t_var					*ft_lstdup(t_var *var);
t_var					*ft_lstget(t_var *var, int index);
t_var					*ft_lstlast(t_var *var);
t_var					*ft_lstnew(char *content);
int						ft_lstsize(t_var *var);
t_var					*ft_sortlst(t_var *var);

/* Libft */
char					*ft_calloc(int count, int size);
void					ft_error(char *type, int is_exit);
int						ft_find_index(char *s, char c);
char					*ft_insert(char *s1, char c, char *s2);
int						ft_isalnum(int c);
char					*ft_itoa(int n);
void					ft_n_putstr(char *s, int n);
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

#endif