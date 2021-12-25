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

static char	*__free(char **backup)
{
	if (*backup)
		free(*backup);
	return (NULL);
}

// static int	__split_backup(char **backup, char **line, int start, int end)
// {
// 	char *temp;

// 	*line = ft_substr(*backup, 0, start);
// 	if (*line)
// 		return (0);
// 	temp = *backup;
// 	*backup = ft_substr(*backup, start, end);
// 	// free(temp);
// 	if (*backup)
// 		return (0);	
// 	free(temp);
// 	return (1);
// }

// 초기화와 백업에 nl이 어디있는지 알려주는
static int	__backup(char **backup, char *buf)
{
	char *temp;

	if (*backup == NULL)
	{
		*backup = ft_substr("", 0, 0);
		if (!(*backup))
			return (-2);
	}
	temp = *backup;
	*backup = ft_strjoin(*backup, buf);
	free(temp);
	return (__get_nl_idx(*backup));
}

char	*get_next_line(int fd)
{
	char	buf[BUFFER_SIZE + 1];
	char	*line;
	char	*temp;
	static char	*backup;
	int nl_idx;
	int rcnt;

	line = NULL;
	rcnt = read(fd, buf, BUFFER_SIZE);
	if (rcnt == -1)
	{
		//__free()   // 읽기실패했으니 free 해줘야 해
		return (__free(&backup));
	}
	buf[rcnt] = 0;
	// if rcnt == 0 ? 아무것도 읽어들인게 없고 && 백업도 null || backup길이가0이라면
	if (rcnt == 0 && (backup == NULL || ft_strlen(backup) == 0))
	{
		// 더이상 할게없다. 진정한 종료.
		return (__free(&backup));
	}

	// 뭔가 읽어왔다면 // 일단 갖다붙혀
	nl_idx = __backup(&backup, buf);

	// printf("자르기전 buf: %s\n", buf);
	// printf("rcnt: %d\n", rcnt);
	// printf("자르기전 backup: %s\n", backup);
	// printf("자르기전 backup len: %zu\n", ft_strlen(backup));
	// printf("nl_idx: %d\n", nl_idx);
	
	// backup 할당에 실패했단 뜻
	if (nl_idx == -2)
		return (NULL);
	else if (nl_idx == -1)
	{
		// \n이 없다. backup그대로 출력하면 끝???이 아니야. 끝까지 읽어들였는지 확인을 해야 해.
		// rcnt == 0. 다 읽어 들였다는거.
		// nl_idx == -1. 줄바꿈도 없다는거.
		if (rcnt == 0)
		{
			line = ft_substr(backup, 0, ft_strlen(backup));
			temp = backup;
			backup = NULL;
			free(temp);
			// __split_backup(&backup, &line, ft_strlen(backup), ft_strlen(backup));
		}
		while (!line)
			line = get_next_line(fd);
	}
	else
	{
		line = ft_substr(backup, 0, nl_idx + 1);
		temp = backup;
		backup = ft_substr(backup, nl_idx + 1, ft_strlen(backup) - (nl_idx + 1));
		free(temp);
		// __split_backup(&backup, &line, nl_idx + 1, ft_strlen(backup) - (nl_idx + 1));
	}
	return (line);
}
