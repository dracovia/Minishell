/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kal-mawl <kal-mawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 17:47:36 by kal-mawl          #+#    #+#             */
/*   Updated: 2026/06/19 14:59:06 by kal-mawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

static void	exec_child(t_shell *shell, t_cmd *cmd, int in_fd, int fd[2])
{
	setup_signals_exec();
	if (fd[0] != STDIN_FILENO)
		close(fd[0]);
	setup_child_fds(in_fd, fd[1]);
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

static int	wait_all(pid_t last_pid)
{
	int		status;
	int		last_status;
	pid_t	pid;

	last_status = 0;
	while (1)
	{
		pid = wait(&status);
		if (pid <= 0)
			break ;
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_status = 128 + WTERMSIG(status);
		}
	}
	return (last_status);
}

int	execute_pipeline(t_shell *shell, t_cmd *cmd)
{
	int		fd[2];
	int		in_fd;
	pid_t	pid;
	pid_t	last_pid;

	in_fd = STDIN_FILENO;
	last_pid = -1;
	while (cmd)
	{
		if (setup_pipe(cmd, fd))
			return (1);
		pid = fork();
		if (pid < 0)
			return (perror("fork"), 1);
		if (pid == 0)
			exec_child(shell, cmd, in_fd, fd);
		last_pid = pid;
		handle_parent(in_fd, fd);
		in_fd = fd[0];
		cmd = cmd->next;
	}
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	return (wait_all(last_pid));
}
