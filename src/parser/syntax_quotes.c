/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassad <mfassad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 21:27:57 by mfassad           #+#    #+#             */
/*   Updated: 2026/03/10 01:46:18 by mfassad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
// scan the raw line
// track quote state
// detect whether quotes are properly closed

// state == Q_SINGLE || state == Q_DOUBLE 
int	is_in_quotes(t_quote_type state)
{
    return (state != Q_NONE);
}
// Checks whether char is ' or "
int	is_quote_char(char c)
{
    return (c == '\'' || c == '"');
}
// Given the current state and the current character, decide the next state.
t_quote_type	update_quote_state(t_quote_type state, char c)
{
    if (is_quote_char(c))
    {
        if (state == Q_NONE)
            state = (c == '\'') ? Q_SINGLE : Q_DOUBLE;
        else if ((state == Q_SINGLE && c == '\'')
            || (state == Q_DOUBLE && c == '"'))
            state = Q_NONE;
    }
    return (state);
}
//Scans the whole input line and checks whether quote state returns to Q_NONE at the end.
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

