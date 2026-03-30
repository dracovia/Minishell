#include "../../include/execution.h"

static void	exec_child(t_shell *shell, t_cmd *cmd, int in_fd, int out_fd)
{
	char	*path;

	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd != STDOUT_FILENO)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
	if (redirection(cmd->redirs))
		exit(1);
	if (is_builtin(cmd->argv[0]))
		exit(exec_builtin(shell, cmd));
	path = get_cmd_path(cmd->argv[0], shell->envp);
	if (!path)
	{
		printf("minishell: %s: command not found\n", cmd->argv[0]);
		exit(127);
	}
	execve(path, cmd->argv, shell->envp);
	perror("execve");
	exit(1);
}

static void	setup_pipe(t_cmd *cmd, int fd[2])
{
	if (cmd->next)
		pipe(fd);
	else
	{
		fd[0] = STDIN_FILENO;
		fd[1] = STDOUT_FILENO;
	}
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

	while (wait(&status) > 0)
		;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	execute_pipeline(t_shell *shell, t_cmd *cmd)
{
	int		fd[2];
	int		in_fd;
	pid_t	pid;

	in_fd = STDIN_FILENO;
	while (cmd)
	{
		setup_pipe(cmd, fd);
		pid = fork();
		if (pid == 0)
			exec_child(shell, cmd, in_fd, fd[1]);
		handle_parent(in_fd, fd);
		in_fd = fd[0];
		cmd = cmd->next;
	}
	return (wait_all());
}

