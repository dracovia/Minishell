#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include "builtins.h"

int		execute_commands(t_shell *shell, t_cmd *cmd);
int		execute_single(t_shell *shell, t_cmd *cmd);
int		execute_pipeline(t_shell *shell, t_cmd *cmd);
int		redirection(t_redir *redir);
int	    handle_heredoc(char *delimiter);
int	    process_all_heredocs(t_cmd *cmds);

char	*get_cmd_path(char *cmd, char **envp);
char	*get_env_valuee(char *name, char **envp);

void	wait_children(pid_t last_pid, t_shell *shell);
void	setup_signals_exec(void);
void	setup_signals_interactive(void);
void	setup_child_fds(int in_fd, int out_fd);
void	exec_cmd(t_shell *shell, t_cmd *cmd);

int		get_signal_status(void);
void	reset_signal_status(void);

#endif