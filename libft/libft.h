/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponcele <gponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 18:07:27 by gponcele          #+#    #+#             */
/*   Updated: 2022/11/25 13:37:44 by gponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>

size_t					ft_strlen(const char *s);
char					*ft_strnstr(const char *haystack,
							const char *needle, size_t len);
int						ft_strncmp(const char *s1,
							const char *s2, size_t n);
char					*ft_strnstr2(const char *haystack,
							const char *needle, size_t len);
char					*ft_strdup(char *str);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_strjoin2(char *str, char c);
int						ft_isalnum(int c);
char					*ft_strchr(const char *s, int c);
char					*ft_calloc(int count, int size);
char					**ft_split(char const *s, char c);
char					*ft_substr(char const *s,
							unsigned int start, size_t len);

#endif