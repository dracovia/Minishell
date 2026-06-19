/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kal-mawl <kal-mawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 15:24:06 by kal-mawl          #+#    #+#             */
/*   Updated: 2026/06/19 15:35:05 by kal-mawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../../include/execution.h"

void	setup_signals_exec(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGPIPE, SIG_DFL);
}

int	handle_single_redir(t_redir *redir)
{
	if (redir->type == T_REDIR_IN)
		return (handle_in(redir->target));
	else if (redir->type == T_REDIR_OUT)
		return (handle_out(redir->target));
	else if (redir->type == T_APPEND)
		return (handle_append(redir->target));
	else if (redir->type == T_HEREDOC)
		return (handle_heredoc_redir(redir));
	return (0);
}

void	free_envp(char **envp)
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
