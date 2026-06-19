/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kal-mawl <kal-mawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 15:58:25 by kal-mawl          #+#    #+#             */
/*   Updated: 2026/06/19 16:39:50 by kal-mawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"
#include "../../include/minishell.h"
#include "../../libft/libft.h"
#include "get_next_line/get_next_line.h"
#include <readline/readline.h>
#include <readline/history.h>

int	is_delimiter(char *line, char *delimiter)
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

int	write_heredoc_line(t_shell *shell, int write_fd,
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

int	read_heredoc_input(t_shell *shell, int write_fd,
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

int	wait_heredoc_child(pid_t pid, int fd_read)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		close(fd_read);
		write(1, "\n", 1);
		return (-1);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		close(fd_read);
		return (-1);
	}
	return (fd_read);
}
