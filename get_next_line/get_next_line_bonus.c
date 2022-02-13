/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghunka <sanghunka@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 21:06:18 by sanghunka         #+#    #+#             */
/*   Updated: 2022/02/13 12:02:19 by sanghunka        ###   ########.fr       */
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

static char	*__free(char **backup, char **buf)
{
	if (*backup)
		free(*backup);
	if (*buf)
		free(*buf);
	return (NULL);
}

static char	*__split(char **backup, int nl_idx)
{
	char		*line;
	char		*temp;
	const int	len = ft_strlen(*backup);

	temp = *backup;
	if (nl_idx == -1)
	{
		line = ft_substr(*backup, 0, len);
		*backup = NULL;
	}
	else
	{
		line = ft_substr(*backup, 0, nl_idx + 1);
		*backup = ft_substr(*backup, nl_idx + 1, len - (nl_idx + 1));
		if (ft_strlen(*backup) == 0)
		{
			free(*backup);
			*backup = NULL;
		}
	}
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
	static char	*b[OPEN_MAX];
	char		*buf;
	int			read_cnt;
	int			nl_idx;

	if (fd < 0)
		return (NULL);
	buf = (char *)malloc(BUFFER_SIZE + 1);
	if (buf == NULL)
		return (NULL);
	read_cnt = read(fd, buf, BUFFER_SIZE);
	if (read_cnt < 0 || ((read_cnt == 0) && (b[fd] == NULL)))
		return (__free(&(b[fd]), &buf));
	nl_idx = __join(&(b[fd]), buf, read_cnt);
	while (nl_idx == -1)
	{
		if (read_cnt == 0)
			break ;
		read_cnt = read(fd, buf, BUFFER_SIZE);
		nl_idx = __join(&(b[fd]), buf, read_cnt);
	}
	if (nl_idx == -2)
		return (__free(&(b[fd]), &buf));
	free(buf);
	return (__split(&(b[fd]), nl_idx));
}
