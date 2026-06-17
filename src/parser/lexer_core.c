/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassad <mfassad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 21:27:12 by mfassad           #+#    #+#             */
/*   Updated: 2026/06/17 23:07:43 by mfassad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	skip_spaces(char *line, int i)
{
	while (line[i] && is_space(line[i]))
		i++;
	return (i);
}

int	handle_token(char *line, int *i, t_token **tokens)
{
	if (is_operator_char(line[*i]))
		return (handle_operator_token(line, i, tokens));
	return (handle_word_token(line, i, tokens));
}

t_token	*lexer(char *line)
{
	t_token	*tokens;
	int		i;

	tokens = NULL;
	i = 0;
	if (!line)
		return (NULL);
	while (line[i])
	{
		i = skip_spaces(line, i);
		if (!line[i])
			break ;
		if (!handle_token(line, &i, &tokens))
		{
			free_token_list(tokens);
			return (NULL);
		}
	}
	return (tokens);
}
