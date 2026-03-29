/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassad <mfassad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 21:27:19 by mfassad           #+#    #+#             */
/*   Updated: 2026/03/12 23:39:08 by mfassad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// keep reading until you hit a space or operator while outside quotes

int	word_len(char *line, int i)
{
	int				len;
	t_quote_type	quote;

	len = 0;
	quote = Q_NONE;
	while (line[i])
	{
		if (quote == Q_NONE && (is_space(line[i])
				|| is_operator_char(line[i])))
			break ;
		quote = update_quote_state(quote, line[i]);
		len++;
		i++;
	}
	return (len);
}

char	*extract_word(char *line, int *i)
{
	int		len;
	int		j;
	char	*word;

	len = word_len(line, *i);
	word = (char *)malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	j = 0;
	while (j < len)
	{
		word[j] = line[*i + j];
		j++;
	}
	word[j] = '\0';
	*i += len;
	return (word);
}

t_quote_type	get_word_quote_type(char *word)
{
	if (!word)
		return (Q_NONE);
	if (word[0] == '\'')
		return (Q_SINGLE);
	if (word[0] == '"')
		return (Q_DOUBLE);
	return (Q_NONE);
}

t_token	*create_word_token(char *line, int *i)
{
	t_token	*token;
	char	*word;

	word = extract_word(line, i);
	if (!word)
		return (NULL);
	token = new_token(word, T_WORD, get_word_quote_type(word));
	if (!token)
	{
		free(word);
		return (NULL);
	}
	return (token);
}

int	handle_word_token(char *line, int *i, t_token **tokens)
{
	t_token	*new_token;

	new_token = create_word_token(line, i);
	if (!new_token)
		return (0);
	if (!append_token(tokens, new_token))
	{
		free(new_token->value);
		free(new_token);
		return (0);
	}
	return (1);
}