/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassad <mfassad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 21:27:36 by mfassad           #+#    #+#             */
/*   Updated: 2026/03/13 19:26:14 by mfassad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

char	*token_type_str(t_token_type type)
{
	if (type == T_WORD)
		return ("WORD");
	if (type == T_PIPE)
		return ("PIPE");
	if (type == T_REDIR_IN)
		return ("REDIR_IN");
	if (type == T_REDIR_OUT)
		return ("REDIR_OUT");
	if (type == T_HEREDOC)
		return ("HEREDOC");
	if (type == T_APPEND)
		return ("APPEND");
	return ("UNKNOWN");
}

void	print_token_list(t_token *tokens)
{
	while (tokens)
	{
		printf("[TOKEN] type=%s value=%s\n",
			token_type_str(tokens->type), tokens->value);
		tokens = tokens->next;
	}
}

void	print_argv(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		printf("  argv[%d] = %s\n", i, argv[i]);
		i++;
	}
}

void	print_redir_list(t_redir *redirs)
{
	while (redirs)
	{
		printf("  [REDIR] type=%d target=%s\n",
			redirs->type, redirs->target);
		redirs = redirs->next;
	}
}

void	print_cmd_list(t_cmd *cmds)
{
	int	index;

	index = 0;
	while (cmds)
	{
		printf("[CMD %d]\n", index);
		print_argv(cmds->argv);
		print_redir_list(cmds->redirs);
		cmds = cmds->next;
		index++;
	}
}