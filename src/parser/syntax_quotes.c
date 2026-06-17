/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassad <mfassad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 21:27:57 by mfassad           #+#    #+#             */
/*   Updated: 2026/06/17 23:17:03 by mfassad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_in_quotes(t_quote_type state)
{
	return (state != Q_NONE);
}

int	is_quote_char(char c)
{
	return (c == '\'' || c == '"');
}

t_quote_type	update_quote_state(t_quote_type state, char c)
{
	if (is_quote_char(c))
	{
		if (state == Q_NONE)
		{
			if (c == '\'')
				state = Q_SINGLE;
			else
				state = Q_DOUBLE;
		}
		else if ((state == Q_SINGLE && c == '\'')
			|| (state == Q_DOUBLE && c == '"'))
			state = Q_NONE;
	}
	return (state);
}

int	has_unclosed_quotes(char *line)
{
	t_quote_type	state;

	if (!line)
		return (0);
	state = Q_NONE;
	while (*line)
	{
		state = update_quote_state(state, *line);
		line++;
	}
	return (is_in_quotes(state));
}
