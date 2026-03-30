#include "../../include/execution.h"

static void	exec_child(t_shell *shell, t_cmd *cmd, int in_fd, int out_fd)
{
	setup_signals_exec();
	setup_child_fds(in_fd, out_fd);
	if (redirection(cmd->redirs))
		exit(1);
	exec_cmd(shell, cmd);
}

static int	setup_pipe(t_cmd *cmd, int fd[2])
{
	if (cmd->next)
	{
		if (pipe(fd) < 0)
			return (perror("pipe"), 1);
	}
	else
	{
		fd[0] = STDIN_FILENO;
		fd[1] = STDOUT_FILENO;
	}
	return (0);
}

static void	handle_parent(int in_fd, int fd[2])
{
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	if (fd[1] != STDOUT_FILENO)
		close(fd[1]);
}

static int	wait_all(void)
{
	int	status;
	int	last_status;

	last_status = 0;
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			last_status = 128 + WTERMSIG(status);
	}
	return (last_status);
}

int	execute_pipeline(t_shell *shell, t_cmd *cmd)
{
	int		fd[2];
	int		in_fd;
	pid_t	pid;

	in_fd = STDIN_FILENO;
	while (cmd)
	{
		if (setup_pipe(cmd, fd))
			return (1);
		pid = fork();
		if (pid < 0)
			return (perror("fork"), 1);
		if (pid == 0)
			exec_child(shell, cmd, in_fd, fd[1]);
		handle_parent(in_fd, fd);
		in_fd = fd[0];
		cmd = cmd->next;
	}
	return (wait_all());
}