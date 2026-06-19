/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kal-mawl <kal-mawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 15:09:52 by kal-mawl          #+#    #+#             */
/*   Updated: 2026/06/19 15:18:52 by kal-mawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/execution.h"
#include "../libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

static void	execute_user_input(t_shell *shell, char *input)
{
	t_parser	*parser;

	parser = parse_input(input, shell->envp, shell->last_status);
	if (!parser)
	{
		ft_putstr_fd("minishell: syntax error\n", 2);
		shell->last_status = 2;
		return ;
	}
	shell->parser = parser;
	shell->cmds = parser->cmds;
	shell->last_status = execute_commands(shell, parser->cmds);
	shell->parser = NULL;
	shell->cmds = NULL;
	free_parser(parser);
}

void	handle_input_loop(t_shell *shell, char *input)
{
	int	signal_status;

	signal_status = get_signal_status();
	if (signal_status)
		shell->last_status = signal_status;
	if (input[0])
	{
		add_history(input);
		execute_user_input(shell, input);
	}
	free(input);
}

static char	*build_shlvl_string(int shlvl_val)
{
	char	*num_str;
	char	*result;

	num_str = ft_itoa(shlvl_val);
	if (!num_str)
		return (NULL);
	result = ft_strjoin("SHLVL=", num_str);
	free(num_str);
	return (result);
}

void	update_shlvl(char **envp)
{
	char	*shlvl_str;
	char	*new_shlvl;
	int		shlvl_val;
	int		i;

	shlvl_str = get_env_valuee("SHLVL", envp);
	if (!shlvl_str)
		shlvl_val = 1;
	else
		shlvl_val = ft_atoi(shlvl_str) + 1;
	new_shlvl = build_shlvl_string(shlvl_val);
	if (!new_shlvl)
		return ;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "SHLVL=", 6) == 0)
		{
			free(envp[i]);
			envp[i] = new_shlvl;
			return ;
		}
		i++;
	}
	free(new_shlvl);
}

char	**free_envp_partial(char **envp, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(envp[i]);
		i++;
	}
	free(envp);
	return (NULL);
}
