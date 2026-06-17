/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassad <mfassad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 08:52:37 by mfassad           #+#    #+#             */
/*   Updated: 2026/06/17 23:05:54 by mfassad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_unquoted_len(char *str)
{
	int				len;
	int				i;
	t_quote_type	quote;

	len = 0;
	i = 0;
	quote = Q_NONE;
	while (str[i])
	{
		if ((str[i] == '\'' && quote == Q_NONE)
			|| (str[i] == '"' && quote == Q_NONE)
			|| (str[i] == '\'' && quote == Q_SINGLE)
			|| (str[i] == '"' && quote == Q_DOUBLE))
			quote = update_quote_state(quote, str[i]);
		else
			len++;
		i++;
	}
	return (len);
}

char	*remove_quotes_from_value(char *str)
{
	char			*new_str;
	int				i;
	int				j;
	t_quote_type	quote;

	new_str = malloc(sizeof(char) * (count_unquoted_len(str) + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	quote = Q_NONE;
	while (str[i])
	{
		if ((str[i] == '\'' && quote == Q_NONE)
			|| (str[i] == '"' && quote == Q_NONE)
			|| (str[i] == '\'' && quote == Q_SINGLE)
			|| (str[i] == '"' && quote == Q_DOUBLE))
			quote = update_quote_state(quote, str[i]);
		else
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

int	remove_quotes_from_tokens(t_token *tokens)
{
	char	*new_value;

	while (tokens)
	{
		if (tokens->type == T_WORD)
		{
			new_value = remove_quotes_from_value(tokens->value);
			if (!new_value)
				return (0);
			free(tokens->value);
			tokens->value = new_value;
		}
		tokens = tokens->next;
	}
	return (1);
}
