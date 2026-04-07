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
