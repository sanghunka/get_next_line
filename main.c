#include "get_next_line.h"

int main(void)
{
	int fd;
	// fd = open("data.txt", O_RDWR);
	fd = open("empty.txt", O_RDWR);

	// char	*line;
	// line = get_next_line(fd);
	// while (line != NULL)
	// {
	// 	printf("----------\n");
	// 	printf("printf: %s\n", line);
	// 	printf("----------\n");

	// 	free(line);
	// 	line = get_next_line(fd);
	// }	

	
	
	close(fd);
	printf("1: %s\n", get_next_line(fd));


	return 0;
}

