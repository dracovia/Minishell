/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassad <mfassad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 21:27:16 by mfassad           #+#    #+#             */
/*   Updated: 2026/03/12 23:45:39 by mfassad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

t_token_type	get_operator_type(char *line)
{
	if (line[0] == '|')
		return (T_PIPE);
	if (line[0] == '>' && line[1] == '>')
		return (T_APPEND);
	if (line[0] == '>')
		return (T_REDIR_OUT);
	if (line[0] == '<' && line[1] == '<')
		return (T_HEREDOC);
	if (line[0] == '<')
		return (T_REDIR_IN);
	return (T_WORD);
}

char	*get_operator_value(char *line)
{
	if (line[0] == '|')
		return (ft_strdup("|"));
	if (line[0] == '>' && line[1] == '>')
		return (ft_strdup(">>"));
	if (line[0] == '>')
		return (ft_strdup(">"));
	if (line[0] == '<' && line[1] == '<')
		return (ft_strdup("<<"));
	if (line[0] == '<')
		return (ft_strdup("<"));
	return (NULL);
}

t_token	*create_operator_token(char *line)
{
	char	*value;

	value = get_operator_value(line);
	if (!value)
		return (NULL);
	return (new_token(value, get_operator_type(line), Q_NONE));
}

int	handle_operator_token(char *line, int *i, t_token **tokens)
{
	t_token	*new_token;

	new_token = create_operator_token(&line[*i]);
	if (!new_token)
		return (0);
	if (!append_token(tokens, new_token))
	{
		free(new_token->value);
		free(new_token);
		return (0);
	}
	*i += operator_len(&line[*i]);
	return (1);
}
