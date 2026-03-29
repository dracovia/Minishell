/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_operators_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassad <mfassad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 02:18:56 by mfassad           #+#    #+#             */
/*   Updated: 2026/03/10 02:19:24 by mfassad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_operator_char(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

int	operator_len(char *line)
{
	if ((line[0] == '>' && line[1] == '>')
		|| (line[0] == '<' && line[1] == '<'))
		return (2);
	return (1);
}

int	has_next_word(char *line, int i)
{
	while (line[i] && (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13)))
		i++;
	return (line[i] && !is_operator_char(line[i]));
}

int	prev_non_space_index(char *line, int i)
{
	i--;
	while (i >= 0 && (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13)))
		i--;
	return (i);
}