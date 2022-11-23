/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 18:07:27 by gponcele          #+#    #+#             */
/*   Updated: 2022/11/23 11:28:45 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>

void					ft_putstr_fd(char *s, int fd);
char					**ft_split(char const *s, char c);
char					*ft_strdup(char *str);
char					*ft_strjoin(char const *s1, char const *s2);
size_t					ft_strlcpy(char *dest, const char *src, size_t size);
size_t					ft_strlen(const char *s);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
char					*ft_strnstr(const char *haystack, const char *needle, size_t len);
char					*ft_strnstr2(const char *haystack, const char *needle, size_t len);
char					*ft_substr(char const *s, unsigned int start, size_t len);

#endif