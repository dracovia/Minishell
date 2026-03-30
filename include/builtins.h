#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int	is_builtin(char *cmd);
int	exec_builtin(t_shell *shell, t_cmd *cmd);

int	builtin_echo(char **argv);
int	builtin_pwd(void);
int	builtin_env(char **envp);

int	builtin_cd(t_shell *shell, char **argv);
int	builtin_export(t_shell *shell, char **argv);
int	builtin_unset(t_shell *shell, char **argv);
int	builtin_exit(t_shell *shell, char **argv);

#endif