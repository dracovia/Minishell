/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassad <mfassad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 21:27:46 by mfassad           #+#    #+#             */
/*   Updated: 2026/03/13 17:55:00 by mfassad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_redir_token(t_token_type type)
{
	return (type == T_REDIR_IN || type == T_REDIR_OUT
		|| type == T_HEREDOC || type == T_APPEND);
}

t_redir	*new_redir(char *target, t_token_type type, t_quote_type quote)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->target = target;
	redir->type = type;
	redir->quote = quote;
	redir->next = NULL;
	return (redir);
}

t_redir	*last_redir(t_redir *redirs)
{
	if (!redirs)
		return (NULL);
	while (redirs->next)
		redirs = redirs->next;
	return (redirs);
}

int	append_redir(t_redir **redirs, t_redir *new_redir)
{
	t_redir	*last;

	if (!redirs || !new_redir)
		return (0);
	if (!*redirs)
	{
		*redirs = new_redir;
		return (1);
	}
	last = last_redir(*redirs);
	last->next = new_redir;
	return (1);
}

void	free_redir_list(t_redir *redirs)
{
	t_redir	*tmp;

	while (redirs)
	{
		tmp = redirs->next;
		free(redirs->target);
		free(redirs);
		redirs = tmp;
	}
}