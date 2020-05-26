#include <stdio.h>
#include <fcntl.h>
#include "get_next_line_bonus.h"

#define DISPLAY(ret, fd)                                             \
	printf(">> R %d fd %d | Line \"%s\"\n", ret, fd, line); 

int main(int argc, char*argv[])
{
	char *line;
	int fd[FOPEN_MAX];
	int ret[FOPEN_MAX];

	fd[0] = 0;
	ret[0] = 0;
	line = NULL;
	if (argc == 2)
	{
		if ((fd[0] = open(argv[1], O_RDONLY))== -1)
			return (1);
		while ((ret[0] = get_next_line(fd[0], &line)) > 0)
		{
			DISPLAY(ret[0], fd[0]);
			free(line);
		}
		DISPLAY(ret[0], fd[0]);
		free(line);
	}
	if (argc == 3)
	{
		if ((fd[0] = open(argv[1], O_RDONLY)) == -1)
			return (1);
		if ((fd[1] = open(argv[2], O_RDONLY)) == -1)
			return (1);
		ret[0] = 1;
		ret[1] = 1;
		
		while (ret[0] > 0 && ret[1] > 0)
		{
			if ((ret[0] = get_next_line(fd[0], &line)) >= 0)
			{
				DISPLAY(ret[0], fd[0]);
				free(line);
				line = NULL;
			}
			if ((ret[1] = get_next_line(fd[1], &line)) >= 0)
			{
				DISPLAY(ret[1], fd[1]);
				free(line);
				line = NULL;
			}
		}
		free(line);
		close(fd[0]);
		close(fd[1]);
	}
	else if (argc > 3)
	{
		int i = 1;
		
		while (i < argc)
		{
			fd[i] = open(argv[i], O_RDONLY);
			printf("argc %d | %i", argc, i);
			while ((ret[i] = get_next_line(fd[i], &line) > 0))
			{
				DISPLAY(ret[i], fd[i]);
				free(line);
				line = NULL;
			}
			DISPLAY(ret[i], fd[i]);
			free(line);
			line = NULL;
			close(fd[i]);
			i++;
		}
	}
	return (0);
}
