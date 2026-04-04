#include "../../include/execution.h"

static int handle_in(char *file)
{
    int fd;
    
    fd = open(file, O_RDONLY);
    if (fd < 0)
		return (perror(file), 1);
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		close(fd);
		return (1);
	}
    close(fd);
    return (0);
}

static int handle_out(char *file)
{
    int fd;

    fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
		return (perror(file), 1);
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		close(fd);
		return (1);
	}
    close(fd);
    return (0);
}

static int handle_append(char *file)
{
    int fd;

    fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (perror(file), 1);
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

static int	handle_single_redir(t_redir *redir)
{
	int	fd;

	if (redir->type == T_REDIR_IN)
		return (handle_in(redir->target));
	else if (redir->type == T_REDIR_OUT)
		return (handle_out(redir->target));
	else if (redir->type == T_APPEND)
		return (handle_append(redir->target));
	else if (redir->type == T_HEREDOC)
	{
		fd = handle_heredoc(redir->target);
		if (fd < 0)
			return (1);
		if (dup2(fd, STDIN_FILENO) < 0)
		{
			perror("dup2");
			close(fd);
			return (1);
		}
		close(fd);
	}
	return (0);
}

int	redirection(t_redir *redir)
{
	while (redir)
	{
		if (handle_single_redir(redir))
			return (1);
		redir = redir->next;
	}
	return (0);
}
