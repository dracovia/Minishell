#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include "builtins.h"

int		execute_commands(t_shell *shell, t_cmd *cmd);

int		execute_single(t_shell *shell, t_cmd *cmd);
int		execute_pipeline(t_shell *shell, t_cmd *cmd);

int		redirection(t_redir *redir);

char	*get_cmd_path(char *cmd, char **envp);

void	wait_children(pid_t last_pid, t_shell *shell);
int	    handle_heredoc(char *delimiter);

#endif