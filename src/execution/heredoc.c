/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kal-mawl <kal-mawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 17:48:00 by kal-mawl          #+#    #+#             */
/*   Updated: 2026/05/14 18:51:01 by kal-mawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"
#include "../../libft/libft.h"
#include "get_next_line/get_next_line.h"

static int	read_heredoc_input(int write_fd, char *delimiter)
{
	char	*line;
	size_t	len;

	len = ft_strlen(delimiter);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line)
			break ;
		if (ft_strlen(line) == len + 1
			&& ft_strncmp(line, delimiter, len) == 0)
		{
			free(line);
			break ;
		}
		write(write_fd, line, ft_strlen(line));
		free(line);
	}
	return (0);
}

int	handle_heredoc(char *delimiter)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (pipe(fd) < 0)
		return (perror("pipe"), -1);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		setup_signals_exec();
		close(fd[0]);
		read_heredoc_input(fd[1], delimiter);
		close(fd[1]);
		exit(0);
	}
	close(fd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		close(fd[0]);
		return (-1);
	}
	return (fd[0]);
}

static int	process_heredocs_in_redir(t_redir *redirs)
{
	while (redirs)
	{
		if (redirs->type == T_HEREDOC)
		{
			redirs->fd = handle_heredoc(redirs->target);
			if (redirs->fd < 0)
				return (-1);
		}
		redirs = redirs->next;
	}
	return (0);
}

int	process_all_heredocs(t_cmd *cmds)
{
	while (cmds)
	{
		if (process_heredocs_in_redir(cmds->redirs) < 0)
			return (-1);
		cmds = cmds->next;
	}
	return (0);
}
