/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kal-mawl <kal-mawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 14:29:16 by kal-mawl          #+#    #+#             */
/*   Updated: 2026/06/19 17:50:50 by kal-mawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include "builtins.h"

int		execute_commands(t_shell *shell, t_cmd *cmd);
int		execute_single(t_shell *shell, t_cmd *cmd);
int		execute_pipeline(t_shell *shell, t_cmd *cmd);
int		redirection(t_redir *redir);
int		handle_heredoc(t_shell *shell, char *delimiter, t_quote_type quote);
int		restore_builtin_fds(int saved_stdin, int saved_stdout);
int		wait_heredoc_child(pid_t pid, int fd_read);
int		handle_single_redir(t_redir *redir);
int		check_direct_path(char *cmd);
int		execve_exit_status(char *cmd);
int		handle_in(char *file);
int		wait_and_get_status(pid_t pid, char *path);
char	*expand_heredoc_line(char *line, t_shell *shell);
char	*get_cmd_path(char *cmd, char **envp);
char	*get_env_value(char *name, char **envp);
char	**free_envp_partial(char **envp, int count);
char	*get_env_valuee(char *name, char **envp);
int		handle_heredoc_redir(t_redir *redir);
int		handle_append(char *file);
int		handle_out(char *file);
int		is_delimiter(char *line, char *delimiter);
int		write_heredoc_line(t_shell *shell, int write_fd, char *line,
			t_quote_type quote);
int		read_heredoc_input(t_shell *shell, int write_fd,
			char *delimiter, t_quote_type quote);
void	wait_children(pid_t last_pid, t_shell *shell);
void	setup_signals_exec(void);
void	setup_signals_interactive(void);
void	setup_child_fds(int in_fd, int out_fd);
void	exec_cmd(t_shell *shell, t_cmd *cmd);
void	handle_input_loop(t_shell *shell, char *input);
void	update_shlvl(char **envp);
void	setup_signals_exec(void);
void	free_envp(char **envp);

int		get_signal_status(void);
void	reset_signal_status(void);
int		prepare_heredocs(t_shell *shell, t_cmd *cmds);
#endif