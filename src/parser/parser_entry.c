/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_entry.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassad <mfassad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 21:27:42 by mfassad           #+#    #+#             */
/*   Updated: 2026/06/17 23:20:26 by mfassad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

t_parser	*parse_input(char *line, char **envp, int last_status)
{
	t_parser	*parser;
	t_token		*tokens;

	if (!validate_input(line))
		return (NULL);
	tokens = build_token_list(line, envp, last_status);
	if (!tokens)
		return (NULL);
	parser = malloc(sizeof(t_parser));
	if (!parser)
	{
		free_token_list(tokens);
		return (NULL);
	}
	parser->tokens = tokens;
	parser->envp = envp;
	parser->last_status = last_status;
	parser->cmds = build_command_list(tokens);
	if (!parser->cmds)
	{
		free_parser(parser);
		return (NULL);
	}
	return (parser);
}

void	free_parser(t_parser *parser)
{
	if (!parser)
		return ;
	free_token_list(parser->tokens);
	free_cmd_list(parser->cmds);
	free(parser);
}

void	free_parser_keep_cmds(t_parser *parser)
{
	if (!parser)
		return ;
	free_token_list(parser->tokens);
	free(parser);
}
