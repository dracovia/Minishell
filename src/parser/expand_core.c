/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassad <mfassad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 21:27:02 by mfassad           #+#    #+#             */
/*   Updated: 2026/03/13 01:45:06 by mfassad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// walk through the token list and expand:
// normal environment variables like $USER
// special status variable $?
// In single quotes, variables should not be expanded
// In double quotes, variables should be expanded
// outside of quotes, variables should be expanded

int	should_expand_var(char *str, int i, t_quote_type quote)
{
	if (str[i] != '$' || quote == Q_SINGLE)
		return (0);
	if (str[i + 1] == '?')
		return (1);
	return (is_var_start(str[i + 1]));
}

int	copy_normal_char(char *str, int *i, char **result, t_quote_type *quote)
{
	char	*tmp;
	char	buf[2];

	*quote = update_quote_state(*quote, str[*i]);
	buf[0] = str[*i];
	buf[1] = '\0';
	tmp = ft_strdup(buf);
	if (!tmp)
		return (0);
	*result = join_and_free(*result, tmp);
	if (!*result)
		return (0);
	(*i)++;
	return (1);
}

int	expand_variable(char *str, int *i, char **result, char **envp)
{
	char	*name;
	char	*value;
	int		len;

	len = var_name_len(&str[*i + 1]);
	name = ft_substr(str, *i + 1, len);
	if (!name)
		return (0);
	value = get_env_value(name, envp);
	free(name);
	if (!value)
		return (0);
	*result = join_and_free(*result, value);
	if (!*result)
		return (0);
	*i += len + 1;
	return (1);
}

char	*expand_token_value(char *value, char **envp, int last_status)
{
	int				i;
	char			*result;
	t_quote_type	quote;

	i = 0;
	quote = Q_NONE;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (value[i])
	{
		if (should_expand_var(value, i, quote) && value[i + 1] == '?')
		{
			if (!expand_status(value, &i, &result, last_status))
				return (expand_fail(result));
		}
		else if (should_expand_var(value, i, quote))
		{
			if (!expand_variable(value, &i, &result, envp))
				return (expand_fail(result));
		}
		else if (!copy_normal_char(value, &i, &result, &quote))
			return (expand_fail(result));
	}
	return (result);
}

int	expand_tokens(t_token *tokens, char **envp, int last_status)
{
	char	*expanded;

	while (tokens)
	{
		if (tokens->type == T_WORD)
		{
			expanded = expand_token_value(tokens->value, envp, last_status);
			if (!expanded)
				return (0);
			free(tokens->value);
			tokens->value = expanded;
		}
		tokens = tokens->next;
	}
	return (1);
}