/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassad <mfassad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 21:27:28 by mfassad           #+#    #+#             */
/*   Updated: 2026/06/17 23:05:10 by mfassad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*next_pipe_token(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == T_PIPE)
			return (tokens);
		tokens = tokens->next;
	}
	return (NULL);
}

t_token	*token_after_pipe(t_token *tokens)
{
	if (!tokens || !tokens->next)
		return (NULL);
	return (tokens->next);
}

int	append_cmd(t_cmd **cmds, t_cmd *new_cmd)
{
	t_cmd	*last;

	if (!cmds || !new_cmd)
		return (0);
	if (!*cmds)
	{
		*cmds = new_cmd;
		return (1);
	}
	last = *cmds;
	while (last->next)
		last = last->next;
	last->next = new_cmd;
	return (1);
}

t_cmd	*parse_pipeline_segment(t_token *start, t_token *end)
{
	return (parse_command(start, end));
}

t_cmd	*parse_pipeline(t_token *tokens)
{
	t_cmd	*cmds;
	t_cmd	*new_cmd;
	t_token	*pipe;

	cmds = NULL;
	while (tokens)
	{
		pipe = next_pipe_token(tokens);
		new_cmd = parse_pipeline_segment(tokens, pipe);
		if (!new_cmd || !append_cmd(&cmds, new_cmd))
			return (free_cmd_list(cmds), NULL);
		if (!pipe)
			break ;
		tokens = token_after_pipe(pipe);
	}
	return (cmds);
}
