/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kal-mawl <kal-mawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 17:48:00 by kal-mawl          #+#    #+#             */
/*   Updated: 2026/06/19 16:40:54 by kal-mawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"
#include "../../include/minishell.h"
#include "../../libft/libft.h"
#include "get_next_line/get_next_line.h"
#include <readline/readline.h>
#include <readline/history.h>

static void	free_envp_child(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

static void	clean_heredoc_child(t_shell *shell, int read_fd, int write_fd)
{
	if (read_fd >= 0)
		close(read_fd);
	if (write_fd >= 0)
		close(write_fd);
	if (shell)
	{
		if (shell->parser)
			free_parser(shell->parser);
		else if (shell->cmds)
			free_cmd_list(shell->cmds);
		free_envp_child(shell->envp);
		free(shell);
	}
	rl_clear_history();
}

static void	heredoc_child(t_shell *shell, int fd[2],
	char *delimiter, t_quote_type quote)
{
	int	ret;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	close(fd[0]);
	ret = read_heredoc_input(shell, fd[1], delimiter, quote);
	clean_heredoc_child(shell, -1, fd[1]);
	exit(ret);
}

int	handle_heredoc(t_shell *shell, char *delimiter, t_quote_type quote)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) < 0)
		return (perror("pipe"), -1);
	pid = fork();
	if (pid < 0)
	{
		close(fd[0]);
		close(fd[1]);
		return (perror("fork"), -1);
	}
	if (pid == 0)
		heredoc_child(shell, fd, delimiter, quote);
	close(fd[1]);
	return (wait_heredoc_child(pid, fd[0]));
}

int	prepare_heredocs(t_shell *shell, t_cmd *cmds)
{
	t_cmd	*cmd;
	t_redir	*redir;
	int		fd;

	cmd = cmds;
	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == T_HEREDOC)
			{
				fd = handle_heredoc(shell, redir->target, redir->quote);
				if (fd < 0)
					return (1);
				if (redir->fd != -1)
					close(redir->fd);
				redir->fd = fd;
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
