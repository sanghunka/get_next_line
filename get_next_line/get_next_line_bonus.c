/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghunka <sanghunka@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 21:06:18 by sanghunka         #+#    #+#             */
/*   Updated: 2021/12/25 22:30:24 by sanghunka        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

static char	*__free(char **backup)
{
	if (*backup)
		free(*backup);
	return (NULL);
}

static char	*__split(char **backup, char **line, int start, int len)
{
	char	*temp;

	*line = ft_substr(*backup, 0, start);
	if (!*line)
		return (NULL);
	temp = *backup;
	*backup = ft_substr(*backup, start, len);
	free(temp);
	if (!*backup)
		return (NULL);
	return (*line);
}

static int	__join(char **backup, char *buf)
{
	char	*temp;

	if (*backup == NULL)
	{
		*backup = ft_substr("", 0, 0);
		if (!(*backup))
			return (-2);
	}
	temp = *backup;
	*backup = ft_strjoin(*backup, buf);
	free(temp);
	if (!*backup)
		return (-2);
	return (__get_nl_idx(*backup));
}

char	*get_next_line(int fd)
{
	static char	*b[10240];
	char		*l;
	char		buf[BUFFER_SIZE + 1];
	int			nl_idx;
	int			read_cnt;

	l = NULL;
	read_cnt = read(fd, buf, BUFFER_SIZE);
	if (read_cnt < 1 && (b[fd] == NULL || ft_strlen(b[fd]) == 0))
		return (__free(&(b[fd])));
	buf[read_cnt] = 0;
	nl_idx = __join(&(b[fd]), buf);
	if (nl_idx >= 0)
		l = __split(&(b[fd]), &l, nl_idx + 1, ft_strlen(b[fd]) - (nl_idx + 1));
	else if (nl_idx == -1)
	{
		if (read_cnt == 0)
			l = __split(&(b[fd]), &l, ft_strlen(b[fd]), ft_strlen(b[fd]));
		while (!l)
			l = get_next_line(fd);
	}
	return (l);
}
