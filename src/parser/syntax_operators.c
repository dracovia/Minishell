/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_operators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassad <mfassad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 20:32:46 by mfassad           #+#    #+#             */
/*   Updated: 2026/03/11 20:38:57 by mfassad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_pipe_invalid(char *line, int i)
{
	int	prev;

	prev = prev_non_space_index(line, i);
	if (prev < 0)
		return (1);
	if (!has_next_word(line, i + 1))
		return (1);
	if (line[i + 1] == '|')
		return (1);
	return (0);
}

static int	is_redir_invalid(char *line, int i)
{
	int	len;

	len = operator_len(&line[i]);
	if ((line[i] == '>' && line[i + 1] == '<')
		|| (line[i] == '<' && line[i + 1] == '>'))
		return (1);
	if (line[i + len] && (line[i + len] == '<' || line[i + len] == '>'))
		return (1);
	if (!has_next_word(line, i + len))
		return (1);
	return (0);
}

int	has_invalid_operators(char *line)
{
	int				i;
	t_quote_type	quote_state;

	i = 0;
	quote_state = Q_NONE;
	while (line[i])
	{
		quote_state = update_quote_state(quote_state, line[i]);
		if (quote_state != Q_NONE || !is_operator_char(line[i]))
			i++;
		else if (line[i] == '|' && is_pipe_invalid(line, i))
			return (1);
		else if (line[i] != '|' && is_redir_invalid(line, i))
			return (1);
		else
			i += operator_len(&line[i]);
	}
	return (0);
}


