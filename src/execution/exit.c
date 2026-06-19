/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kal-mawl <kal-mawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 17:47:49 by kal-mawl          #+#    #+#             */
/*   Updated: 2026/06/19 14:59:57 by kal-mawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>

static int	is_numeric(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static void	free_envp_exit(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

static void	clean_exit_shell(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->parser)
		free_parser(shell->parser);
	else if (shell->cmds)
		free_cmd_list(shell->cmds);
	free_envp_exit(shell->envp);
	rl_clear_history();
	free(shell);
}

int	builtin_exit(t_shell *shell, char **argv)
{
	long	status;

	if (!argv[1])
	{
		status = shell->last_status;
		clean_exit_shell(shell);
		exit(status);
	}
	if (!is_numeric(argv[1]))
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		clean_exit_shell(shell);
		exit(2);
	}
	if (argv[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	status = atol(argv[1]) % 256;
	clean_exit_shell(shell);
	exit(status);
}
