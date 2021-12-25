#include "get_next_line.h"

int main(void)
{
	int fd;
	// fd = open("empty.txt", O_RDWR);
	// fd = open("nl", O_RDWR);
	fd = open("41_with_nl", O_RDWR);

	char	*line;
	line = get_next_line(fd);
	while (line != NULL)
	{
		// printf("----------\n");
		printf("		%s\n", line);
		// printf("----------\n");

		free(line);
		line = get_next_line(fd);
	}	

	// get_next_line(fd);
	// printf("		: %s\n", get_next_line(fd));
	// printf("		: %s\n", get_next_line(fd));
	// printf("		: %s\n", get_next_line(fd));
	// printf("		: %s\n", get_next_line(fd));

	close(fd);

	system("leaks a.out");
	return 0;
}

