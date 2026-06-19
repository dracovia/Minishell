/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kal-mawl <kal-mawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 18:28:36 by mfassad           #+#    #+#             */
/*   Updated: 2026/06/19 15:35:31 by kal-mawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/execution.h"
#include "../libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

static void	free_shell(t_shell *shell)
{
	if (!shell)
		return ;
	free_envp(shell->envp);
	free(shell);
}

static char	**dup_envp(char **envp)
{
	int		i;
	char	**new_envp;

	i = 0;
	while (envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i + 1));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
			return (free_envp_partial(new_envp, i));
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}

static t_shell	*init_shell(char **envp)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->envp = dup_envp(envp);
	if (!shell->envp)
	{
		free(shell);
		return (NULL);
	}
	update_shlvl(shell->envp);
	shell->last_status = 0;
	shell->cmds = NULL;
	shell->parser = NULL;
	return (shell);
}

static int	main_loop(t_shell *shell)
{
	char	*input;

	setup_signals_interactive();
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		handle_input_loop(shell, input);
		reset_signal_status();
	}
	return (shell->last_status);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	int		status;

	(void)argc;
	(void)argv;
	shell = init_shell(envp);
	if (!shell)
		return (1);
	status = main_loop(shell);
	rl_clear_history();
	free_shell(shell);
	return (status);
}
