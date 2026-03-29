/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassad <mfassad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 21:27:32 by mfassad           #+#    #+#             */
/*   Updated: 2026/03/13 17:59:16 by mfassad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// inside one command segment:
// when you see a redirection token, the next token is its target
// together they form one redirection entry

t_redir	*create_redir_node(t_token *op_token, t_token *target_token)
{
	char	*target;

	target = ft_strdup(target_token->value);
	if (!target)
		return (NULL);
	return (new_redir(target, op_token->type, target_token->quote));
}

t_redir	*parse_redirs(t_token *start, t_token *end)
{
	t_redir	*redirs;
	t_redir	*new_node;

	redirs = NULL;
	while (start && start != end)
	{
		if (is_redir_token(start->type) && start->next && start->next != end)
		{
			new_node = create_redir_node(start, start->next);
			if (!new_node || !append_redir(&redirs, new_node))
				return (free_redir_list(redirs), NULL);
			start = start->next;
		}
		start = start->next;
	}
	return (redirs);
}