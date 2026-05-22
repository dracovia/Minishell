/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassad <mfassad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 17:47:29 by kal-mawl          #+#    #+#             */
/*   Updated: 2026/05/22 19:43:23 by mfassad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

static void	close_heredoc_fds(t_cmd *cmd)
{
	t_redir	*redir;

	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == T_HEREDOC && redir->fd >= 0)
			{
				close(redir->fd);
				redir->fd = -1;
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}

int	execute_commands(t_shell *shell, t_cmd *cmd)
{
	int	status;

	if (!shell || !cmd)
		return (1);
	shell->cmds = cmd;
	if (prepare_heredocs(shell, cmd))
	{
		close_heredoc_fds(cmd);
		shell->cmds = NULL;
		shell->last_status = 130;
		return (130);
	}
	if (cmd->next)
		status = execute_pipeline(shell, cmd);
	else
		status = execute_single(shell, cmd);
	close_heredoc_fds(cmd);
	shell->cmds = NULL;
	shell->last_status = status;
	return (status);
}
