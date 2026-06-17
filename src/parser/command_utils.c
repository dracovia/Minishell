/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassad <mfassad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 21:26:59 by mfassad           #+#    #+#             */
/*   Updated: 2026/06/17 23:03:47 by mfassad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_argv(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

char	**free_argv_partial(char **argv, int used)
{
	while (used > 0)
	{
		used--;
		free(argv[used]);
	}
	free(argv);
	return (NULL);
}

t_cmd	*last_cmd(t_cmd *cmds)
{
	if (!cmds)
		return (NULL);
	while (cmds->next)
		cmds = cmds->next;
	return (cmds);
}

void	free_cmd_list(t_cmd *cmds)
{
	t_cmd	*tmp;

	while (cmds)
	{
		tmp = cmds->next;
		free_argv(cmds->argv);
		free_redir_list(cmds->redirs);
		free(cmds);
		cmds = tmp;
	}
}

int	has_redirection(t_token *start, t_token *end)
{
	while (start && start != end)
	{
		if (is_redir_token(start->type))
			return (1);
		start = start->next;
	}
	return (0);
}
