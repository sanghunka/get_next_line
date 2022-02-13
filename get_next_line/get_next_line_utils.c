/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghunka <sanghunka@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 21:53:03 by sanghunka         #+#    #+#             */
/*   Updated: 2022/02/13 00:27:59 by sanghunka        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	const char	*a = s;

	while (*s)
		s++;
	return (s - a);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s = src;

	if (!dst && !src)
		return (NULL);
	d = dst;
	while (n--)
		*d++ = *s++;
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	const size_t	s1_len = ft_strlen(s1);
	const size_t	s2_len = ft_strlen(s2);
	char			*new;

	new = (char *)malloc(s1_len + s2_len + 1);
	if (!new)
		return (NULL);
	ft_memcpy(new, s1, s1_len);
	ft_memcpy(new + s1_len, s2, s2_len);
	*(new + s1_len + s2_len) = '\0';
	return (new);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char				*substr;
	const unsigned int	s_len = ft_strlen(s);
	size_t				size;

	if (s_len + 1 < start)
		size = 1;
	else if (s_len >= start + len)
		size = len + 1;
	else
		size = s_len - start + 1;
	substr = malloc(size);
	if (!substr)
		return (NULL);
	ft_memcpy(substr, s + start, size - 1);
	*(substr + size - 1) = '\0';
	return (substr);
}
