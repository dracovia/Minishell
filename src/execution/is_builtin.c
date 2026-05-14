/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kal-mawl <kal-mawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 17:48:06 by kal-mawl          #+#    #+#             */
/*   Updated: 2026/05/13 17:48:07 by kal-mawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/builtins.h"
# include "../../libft/libft.h"

int is_builtin(char *cmd)
{
    if (ft_strncmp(cmd, "echo", 5) == 0)
        return (1);
    else if (ft_strncmp(cmd, "cd", 3) == 0)
        return (1);
    else if (ft_strncmp(cmd, "pwd", 4) == 0)
        return (1);
    else if (ft_strncmp(cmd, "export", 7) == 0)
        return (1);
    else if (ft_strncmp(cmd, "unset", 6) == 0)
        return (1);
    else if (ft_strncmp(cmd, "env", 4) == 0)
        return (1);
    else if (ft_strncmp(cmd, "exit", 5) == 0)
        return (1);
    return (0);
}

int exec_builtin(t_shell *shell, t_cmd *cmd)
{
    if (!cmd || !cmd->argv || !cmd->argv[0])
        return (1);
    if (ft_strncmp(cmd->argv[0], "echo", 5) == 0)
        return (builtin_echo(cmd->argv));
    else if (ft_strncmp(cmd->argv[0], "cd", 3) == 0)
        return (builtin_cd(shell, cmd->argv));  
    else if (ft_strncmp(cmd->argv[0], "pwd", 4) == 0)
        return (builtin_pwd());
    else if (ft_strncmp(cmd->argv[0], "export", 7) == 0)
        return (builtin_export(shell, cmd->argv));
    else if (ft_strncmp(cmd->argv[0], "unset", 6) == 0)
        return (builtin_unset(shell, cmd->argv));
    else if (ft_strncmp(cmd->argv[0], "env", 4) == 0)
        return (builtin_env(shell->envp));
    else if (ft_strncmp(cmd->argv[0], "exit", 5) == 0)
        return (builtin_exit(shell, cmd->argv));
    return (1);
}


