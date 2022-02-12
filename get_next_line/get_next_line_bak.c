/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bak.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghunka <sanghunka@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 21:06:18 by sanghunka         #+#    #+#             */
/*   Updated: 2022/01/07 05:46:31 by sanghunka        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	int	__get_nl_idx(char *s)
{
	int			i;
	const int	s_len = ft_strlen(s);

	i = 0;
	while (i < s_len)
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

// static char	*__free(char **backup, char **buf)
// {
// 	if (*backup)
// 		free(*backup);
// 	free(*buf);
// 	return (NULL);
// }

static char	*__free(char **backup, char **buf, int is_freeable_buf)
{
	if (*backup)
		free(*backup);
	if (is_freeable_buf)
		free(*buf);
	return (NULL);
}

static char	*__split(char **backup, int nl_idx)
{
	char	*line;
	char	*temp;
	const int	len = ft_strlen(*backup);

	temp = *backup;
	if (nl_idx == -1)
	{
		line = ft_substr(*backup, 0, len);
		*backup = ft_substr("", 0, 0);			
	}
	else
	{
		line = ft_substr(*backup, 0, nl_idx + 1);
		*backup = ft_substr(*backup, nl_idx + 1, len - (nl_idx + 1));
	}
	if (!line)
		return (NULL);
	if (!*backup)
		return (NULL);
	free(temp);		
	return (line);
}

static int	__join(char **backup, char *buf, int read_cnt)
{
	char	*temp;

	if (*backup == NULL)
	{
		*backup = ft_substr("", 0, 0);
		if (!(*backup))
			return (-2);
	}
	temp = *backup;
	*(buf + read_cnt) = '\0';
	*backup = ft_strjoin(*backup, buf);
	free(temp);
	if (!*backup)
		return (-2);
	return (__get_nl_idx(*backup));
}

char	*get_next_line(int fd)
{
	static char	*b;
	char		*buf;
	int			read_cnt;
	int			nl_idx;

	if (fd < 0)
		return (__free(&b, &buf, 0));//return (NULL);
	buf = (char *)malloc(BUFFER_SIZE + 1);
	if (buf == NULL)
		return (__free(&b, &buf, 0));//return (NULL);
	read_cnt = read(fd, buf, BUFFER_SIZE);
	if (read_cnt < 0 || (read_cnt == 0 && (b == NULL || ft_strlen(b) == 0)))
		return (__free(&b, &buf, 1));
	nl_idx = __join(&b, buf, read_cnt);
	while (nl_idx == -1)
	{
		if (read_cnt == 0)
			break;
		read_cnt = read(fd, buf, BUFFER_SIZE);
		nl_idx = __join(&b, buf, read_cnt);
	}
	if (nl_idx == -2)
		return (__free(&b, &buf, 1));
	free(buf);
	return (__split(&b, nl_idx));
}

// char	*get_next_line(int fd)
// {
// 	static char	*b;
// 	char		*buf;
// 	int			read_cnt;

// 	buf = (char *)malloc(BUFFER_SIZE + 1);
// 	if (fd < 0 || buf == NULL)
// 		return (__free(&b, &buf));
// 	read_cnt = read(fd, buf, BUFFER_SIZE);
// 	if (read_cnt < 1 && (b == NULL || ft_strlen(b) == 0))
// 		return (__free(&b, &buf));
// 	*(buf + read_cnt) = '\0';
// 	while (__join(&b, buf) == -1)
// 	{
// 		if (read_cnt == 0)
// 			break;
// 		read_cnt = read(fd, buf, BUFFER_SIZE);
// 		*(buf + read_cnt) = '\0';
// 	}
// 	free(buf);
// 	return (__split(&b));
// }
