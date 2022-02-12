/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghunka <sanghunka@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 21:06:18 by sanghunka         #+#    #+#             */
/*   Updated: 2022/01/07 04:01:33 by sanghunka        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>
#include <stdio.h>

static char	*__free(char **backup, char **buf)
{
	if (*backup)
		free(*backup);
	if (*buf)
		free(*buf);		
	return (NULL);
}


size_t	ft_strlen(const char *s)
{
	const char	*a = s;

	while (*s)
		s++;
	return (s - a);
}

int	main(void)
{
	static char	*b;
	char		*buf;

	// buf = (char *)malloc(BUFFER_SIZE + 1);
	
	if (buf == NULL)
		printf("buf is null\n");
	else
		printf("buf is not null\n");
	
	// printf("%p\n", buf);
	// printf("%c\n", *buf);

	ft_strlen(b);

	// if (*buf)
	// 	printf("*buf is null\n");
	// else
	// 	printf("*buf is not null\n");
	

	return (0);
}