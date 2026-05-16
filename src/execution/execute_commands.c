/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kal-mawl <kal-mawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 17:47:29 by kal-mawl          #+#    #+#             */
/*   Updated: 2026/05/13 17:47:30 by kal-mawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

// Execute command list (single command or pipeline)
int	execute_commands(t_shell *shell, t_cmd *cmd)
{
	if (!shell || !cmd)
		return (1);
	if (cmd->next)
		return (execute_pipeline(shell, cmd));
	return (execute_single(shell, cmd));
}
