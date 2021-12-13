#include "get_next_line.h"


static	int	__get_nl_idx(char *s)
{
	int	i;
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

char	*get_next_line(int fd)
{
	char	*buf;
	char	*line = NULL;
	static char	*backup;
	
	if (fd < 0)
		return (NULL);

	if (backup == NULL)
	{
		printf("\n|| Backup is null\n");
		backup = ft_substr("", 0, 0);
		if (!backup)
			return (NULL); // and free
		// printf("backup init: %zu\n\n", ft_strlen(backup));
	}

	buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!buf)
	{
		// 동적할당해준거 전부 free 해야함
		return (NULL);
	}

	int rcnt;
	rcnt = read(fd, buf, BUFFER_SIZE);
	if (rcnt == -1)
	{
		printf("rcnt == -1\n");
		free(buf);
		free(backup);
		return (NULL);
	}
	*(buf + rcnt) = '\0';
	// printf("backuplen: %zu	rcnt: %d\n\n", ft_strlen(backup), rcnt);

	if (rcnt == 0 && ft_strlen(backup) == 0) //end!!
	{
		// printf("end\n\n");
		return (NULL);
	}
	// 잘 읽어왔다고 가정

	// 일단 갖다 붙여
	backup = ft_strjoin(backup, buf);
	// printf("BEFORE backup: %s\n", backup);

	// int nl = __get_nl_idx(buf);
	// if (nl == -1)
	// {
	// 개행이없다. 전부다 백업뒤에 붙이고
	// backup = ft_strjoin(backup, buf);
	// 또 읽어? 아니면 백업에서 잘라서 프린트해?
	int b_nl = __get_nl_idx(backup);
	// printf("b_nl: %d\n", b_nl);

	// if (b_nl == -1 && rcnt == 0)
	// 	return (NULL);

	while (b_nl == -1)
	{
		rcnt = read(fd, buf, BUFFER_SIZE);
		*(buf + rcnt) = '\0';
		backup = ft_strjoin(backup, buf);
		b_nl = __get_nl_idx(backup);
		if (b_nl == -1 && rcnt == 0)
		{
			line = ft_substr(backup, 0, ft_strlen(backup));
			backup = ft_substr("\0", 0, 1);
			return (line);
		}
	}
	// else
	// {
	line = ft_substr(backup, 0, b_nl);
	backup = ft_substr(backup, b_nl + 1, ft_strlen(backup) - (b_nl + 1));
	// }
	
	// printf("line: %s\n", line);
	// printf("backup: %s\n", backup);
	printf("-----end-----\n");
	return (line);
}