#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include "get_next_line.h"

int	main(void)
{
	char	*s1;

	s1 = strdup("");
	free(s1);
	while (s1)
	{
		s1 = get_next_line(1);
		printf("%s", s1);
		free(s1);
	}
//	system("leaks a.out > leaks_result_temp; cat leaks_result_temp | grep leaked && rm -rf leaks_result_temp");
	return (0);
}
