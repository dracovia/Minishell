/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kal-mawl <kal-mawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 14:29:23 by kal-mawl          #+#    #+#             */
/*   Updated: 2026/06/19 15:56:30 by kal-mawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int		is_builtin(char *cmd);
int		exec_builtin(t_shell *shell, t_cmd *cmd);

int		builtin_echo(char **argv);
int		builtin_pwd(void);
int		builtin_env(char **envp);
int		is_valid(char *str);
int		env_count(char **envp);
int		name_len(char *str);
int		find_var_index(char *name, char **envp);

int		builtin_cd(t_shell *shell, char **argv);
int		builtin_export(t_shell *shell, char **argv);
int		builtin_unset(t_shell *shell, char **argv);
int		builtin_exit(t_shell *shell, char **argv);

void	update_var(char **envp, int index, char *arg);

#endif