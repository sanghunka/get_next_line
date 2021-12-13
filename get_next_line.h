#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

// #define BUFFER_SIZE 10

#include <stdio.h> ////////////
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>


char	*get_next_line(int fd);


// utils
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);

# endif