/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executesingle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kal-mawl <kal-mawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 15:37:14 by kal-mawl          #+#    #+#             */
/*   Updated: 2026/06/19 18:01:55 by kal-mawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>

int	wait_and_get_status(pid_t pid, char *path)
{
	int	status;

	waitpid(pid, &status, WUNTRACED);
	free(path);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	if (WIFSTOPPED(status))
		return (128 + WSTOPSIG(status));
	return (1);
}

int	restore_builtin_fds(int saved_stdin, int saved_stdout)
{
	int	status;

	status = 0;
	if (dup2(saved_stdin, STDIN_FILENO) < 0)
	{
		perror("dup2");
		status = 1;
	}
	if (dup2(saved_stdout, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		status = 1;
	}
	close(saved_stdin);
	close(saved_stdout);
	return (status);
}

int	check_direct_path(char *cmd)
{
	struct stat	st;

	if (!ft_strchr(cmd, '/'))
		return (0);
	if (stat(cmd, &st) < 0)
	{
		perror(cmd);
		return (127);
	}
	if (S_ISDIR(st.st_mode))
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		return (126);
	}
	if (access(cmd, X_OK) < 0)
	{
		perror(cmd);
		return (126);
	}
	return (0);
}
