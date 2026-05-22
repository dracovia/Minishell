/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassad <mfassad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 17:48:00 by kal-mawl          #+#    #+#             */
/*   Updated: 2026/05/22 18:59:51 by mfassad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"
#include "../../include/minishell.h"
#include "../../libft/libft.h"
#include "get_next_line/get_next_line.h"
#include <readline/readline.h>
// library for rl_clear_history()
#include <readline/history.h>

static int	is_delimiter(char *line, char *delimiter)
{
	size_t	len;

	len = ft_strlen(delimiter);
	if (ft_strlen(line) != len + 1)
		return (0);
	if (ft_strncmp(line, delimiter, len) != 0)
		return (0);
	if (line[len] != '\n')
		return (0);
	return (1);
}

static int	write_heredoc_line(t_shell *shell, int write_fd,
	char *line, t_quote_type quote)
{
	char	*expanded;

	if (quote == Q_NONE)
	{
		expanded = expand_heredoc_line(line, shell);
		free(line);
		if (!expanded)
			return (1);
		line = expanded;
	}
	write(write_fd, line, ft_strlen(line));
	free(line);
	return (0);
}

static int	read_heredoc_input(t_shell *shell, int write_fd,
	char *delimiter, t_quote_type quote)
{
	char	*line;

	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (is_delimiter(line, delimiter))
		{
			free(line);
			break ;
		}
		if (write_heredoc_line(shell, write_fd, line, quote))
			return (1);
	}
	return (0);
}

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
	int		status;

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
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		close(fd[0]);
		write(1, "\n", 1);
		return (-1);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		close(fd[0]);
		return (-1);
	}
	return (fd[0]);
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