/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassad <mfassad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 23:19:39 by mfassad           #+#    #+#             */
/*   Updated: 2026/06/17 23:21:27 by mfassad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

int	should_expand_var(char *str, int i, t_quote_type quote)
{
	if (str[i] != '$' || quote == Q_SINGLE)
		return (0);
	if (str[i + 1] == '?')
		return (1);
	return (is_var_start(str[i + 1]));
}

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
