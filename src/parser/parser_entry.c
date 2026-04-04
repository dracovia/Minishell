/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_entry.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassad <mfassad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 21:27:42 by mfassad           #+#    #+#             */
/*   Updated: 2026/04/04 09:29:07 by mfassad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// coordinate the whole parsing process from raw input line to command list.
// validate quotes -> validate operators -> tokenize the line
// -> expand tokens ->parse pipeline into command list->clean temporary token list
// -> return final t_cmd *

int	validate_input(char *line)
{
	if (!line)
		return (0);
	if (has_unclosed_quotes(line))
		return (0);
	if (has_invalid_operators(line))
		return (0);
	return (1);
}

t_token	*build_token_list(char *line, char **envp, int last_status)
{
	t_token	*tokens;

	tokens = lexer(line);
	if (!tokens)
		return (NULL);
	if (!expand_tokens(tokens, envp, last_status))
	{
		free_token_list(tokens);
		return (NULL);
	}
	if (!remove_quotes_from_tokens(tokens))
	{
		free_token_list(tokens);
		return (NULL);
	}
	return (tokens);
}

t_cmd	*build_command_list(t_token *tokens)
{
	if (!tokens)
		return (NULL);
	return (parse_pipeline(tokens));
}

void	cleanup_parser_tokens(t_token *tokens)
{
	free_token_list(tokens);
}

t_cmd	*parse_input(char *line, char **envp, int last_status)
{
	t_token	*tokens;
	t_cmd	*cmds;

	if (!validate_input(line))
		return (NULL);
	tokens = build_token_list(line, envp, last_status);
	if (!tokens)
		return (NULL);
	cmds = build_command_list(tokens);
	cleanup_parser_tokens(tokens);
	return (cmds);
}