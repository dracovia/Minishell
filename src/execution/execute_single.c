/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kal-mawl <kal-mawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 17:47:42 by kal-mawl          #+#    #+#             */
/*   Updated: 2026/06/19 15:45:48 by kal-mawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>

static int	helper(char *error, char *path)
{
	perror(error);
	free(path);
	return (1);
}

static int	execute_builtin_with_redir(t_shell *shell, t_cmd *cmd)
{
	int	saved_stdin;
	int	saved_stdout;
	int	status;

	saved_stdin = dup(STDIN_FILENO);
	if (saved_stdin < 0)
		return (perror("dup"), 1);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdout < 0)
	{
		close(saved_stdin);
		return (perror("dup"), 1);
	}
	if (redirection(cmd->redirs))
	{
		restore_builtin_fds(saved_stdin, saved_stdout);
		return (1);
	}
	status = exec_builtin(shell, cmd);
	if (restore_builtin_fds(saved_stdin, saved_stdout))
		return (1);
	return (status);
}

static void	child_process(t_shell *shell, t_cmd *cmd, char *path)
{
	int	exit_code;

	setup_signals_exec();
	if (redirection(cmd->redirs))
		exit(1);
	execve(path, cmd->argv, shell->envp);
	exit_code = execve_exit_status(cmd->argv[0]);
	free(path);
	exit(exit_code);
}

static int	execute_external(t_shell *shell, t_cmd *cmd)
{
	pid_t	pid;
	char	*path;
	int		status;

	status = check_direct_path(cmd->argv[0]);
	if (status != 0)
		return (status);
	path = get_cmd_path(cmd->argv[0], shell->envp);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		return (127);
	}
	pid = fork();
	if (pid < 0)
		return (helper("fork", path));
	if (pid == 0)
		child_process(shell, cmd, path);
	return (wait_and_get_status(pid, path));
}

int	execute_single(t_shell *shell, t_cmd *cmd)
{
	int	status;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (0);
	if (is_builtin(cmd->argv[0]))
	{
		if (ft_strncmp(cmd->argv[0], "exit", 5) == 0)
			status = exec_builtin(shell, cmd);
		else
			status = execute_builtin_with_redir(shell, cmd);
		shell->last_status = status;
		return (status);
	}
	status = execute_external(shell, cmd);
	shell->last_status = status;
	return (status);
}

/*
execute_single
   ↓
not builtin
   ↓
get_cmd_path → "/bin/ls"
   ↓
fork
   ↓
child → execve("/bin/ls")
   ↓
parent → waitpid
   ↓
update last_status
*/
