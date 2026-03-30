#include "../../include/execution.h"
#include "get_next_line/get_next_line.h"

static int	read_heredoc_input(int write_fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		printf("> ");
		line = get_next_line(0);
		if (!line)
			break ;
		// remove newline for comparison
		if (strncmp(line, delimiter, strlen(delimiter)) == 0
			&& line[strlen(delimiter)] == '\n')
		{
			free(line);
			break ;
		}
		write(write_fd, line, strlen(line));
		free(line);
	}
	return (0);
}

int	handle_heredoc(char *delimiter)
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	read_heredoc_input(fd[1], delimiter);
	close(fd[1]);
	return (fd[0]);
}