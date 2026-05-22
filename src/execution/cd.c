/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassad <mfassad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 17:47:10 by kal-mawl          #+#    #+#             */
/*   Updated: 2026/05/22 21:33:30 by mfassad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../include/minishell.h"
#include "../../include/execution.h"

int	builtin_cd(t_shell *shell, char **argv)
{
	char	*path;

	if (argv[1] && argv[2])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	if (!argv[1])
	{
		path = get_env_valuee("HOME", shell->envp);
		if (!path)
			return (ft_putstr_fd("cd: HOME not set\n", 2), 1);
	}
	else if (ft_strncmp(argv[1], "-", 2) == 0)
	{
		path = get_env_valuee("OLDPWD", shell->envp);
		if (!path)
			return (ft_putstr_fd("cd: OLDPWD not set\n", 2), 1);
	}
	else
		path = argv[1];
	if (chdir(path) != 0)
		return (perror("cd"), 1);
	return (0);
}
