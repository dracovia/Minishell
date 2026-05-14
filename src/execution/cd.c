/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kal-mawl <kal-mawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 17:47:10 by kal-mawl          #+#    #+#             */
/*   Updated: 2026/05/13 17:47:11 by kal-mawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../include/minishell.h"
#include "../../include/execution.h"

int builtin_cd(t_shell *shell, char **argv)
{
    char *path;

    if (!argv[1])
    {
        path = get_env_valuee("HOME", shell->envp);
        if (!path)
        {
            ft_putstr_fd("cd: HOME not set\n", 2);
            return (1);
        }
    }
    else if (ft_strncmp(argv[1], "-", 1) == 0)  // Handle cd -
    {
        path = get_env_valuee("OLDPWD", shell->envp);
        if (!path)
        {
            ft_putstr_fd("cd: OLDPWD not set\n", 2);
            return (1);
        }
    }
    else
        path = argv[1];
    if (chdir(path) != 0)
        return (perror("cd"), 1);
    return (0);
}
