/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kal-mawl <kal-mawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 17:47:42 by kal-mawl          #+#    #+#             */
/*   Updated: 2026/05/13 17:47:43 by kal-mawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

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
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin < 0 || saved_stdout < 0)
		return (perror("dup"), 1);
	if (redirection(cmd->redirs))
	{
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
		return (1);
	}
	status = exec_builtin(shell, cmd);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	return (status);
}

static void	child_process(t_shell *shell, t_cmd *cmd, char *path)
{
   setup_signals_exec();
	if (redirection(cmd->redirs))
		exit(1);
	execve(path, cmd->argv, shell->envp);
	helper("execve", path);
   // free(path);
	exit(1);
}

static int execute_external(t_shell *shell, t_cmd *cmd)
{
   pid_t   pid;
   char    *path;
   int    status;

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
   waitpid(pid, &status, 0);
   free(path);
   if (WIFEXITED(status)) //did the process exit normally?
		return (WEXITSTATUS(status)); // what is the exit code?
   if (WIFSIGNALED(status))
	   return (128 + WTERMSIG(status));
   return (1);
}

int execute_single(t_shell *shell, t_cmd *cmd)
{
   int status;

   if (!cmd || !cmd->argv || !cmd->argv[0])
      return (0);
   if (is_builtin(cmd->argv[0]))
   {
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

/*
execute_single
   ↓
is_builtin ?
   ↓ YES
execute_builtin_with_redir
   ↓
save fds
   ↓
apply redirections
   ↓
exec_builtin
   ↓
restore fds
*/