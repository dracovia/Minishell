/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassad <mfassad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 17:48:19 by kal-mawl          #+#    #+#             */
/*   Updated: 2026/05/22 21:46:04 by mfassad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"
#include "../../libft/libft.h"
#include <errno.h>
#include <sys/stat.h>

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

static int	check_direct_path_child(char *cmd)
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

static int	execve_exit_status(char *cmd)
{
	if (errno == EACCES || errno == EISDIR || errno == ENOEXEC)
		return (126);
	if (errno == ENOENT)
		return (127);
	perror(cmd);
	return (1);
}

void	exec_cmd(t_shell *shell, t_cmd *cmd)
{
	char	*path;
	int		status;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		exit(0);
	if (is_builtin(cmd->argv[0]))
		exit(exec_builtin(shell, cmd));
	status = check_direct_path_child(cmd->argv[0]);
	if (status != 0)
		exit(status);
	path = get_cmd_path(cmd->argv[0], shell->envp);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	execve(path, cmd->argv, shell->envp);
	status = execve_exit_status(cmd->argv[0]);
	free(path);
	exit(status);
}