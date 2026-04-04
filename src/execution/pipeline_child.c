#include "../../include/execution.h"
#include "../../libft/libft.h"

void	setup_child_fds(int in_fd, int out_fd)
{
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
}

void	exec_cmd(t_shell *shell, t_cmd *cmd)
{
	char	*path;

	if (is_builtin(cmd->argv[0]))
		exit(exec_builtin(shell, cmd));
	path = get_cmd_path(cmd->argv[0], shell->envp);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	execve(path, cmd->argv, shell->envp);
	perror("execve");
	free(path);
	exit(1);
}