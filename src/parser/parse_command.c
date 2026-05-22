/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassad <mfassad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 21:27:22 by mfassad           #+#    #+#             */
/*   Updated: 2026/05/22 21:34:08 by mfassad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// normal words go argv and redir syntax goes to t_redir nodes 
 
#include "../../include/minishell.h"
#include "../../libft/libft.h"

static int	should_keep_word(t_token *token)
{
	if (!token || token->type != T_WORD)
		return (0);
	if (token->value[0] == '\0' && token->quote == Q_NONE)
		return (0);
	return (1);
}

int	count_cmd_args(t_token *start, t_token *end)
{
	int	count;

	count = 0;
	while (start && start != end)
	{
		if (is_redir_token(start->type) && start->next != end)
			start = start->next;
		else if (should_keep_word(start))
			count++;
		start = start->next;
	}
	return (count);
}

char	**build_cmd_argv(t_token *start, t_token *end)
{
	char	**argv;
	int		i;
	int		count;

	count = count_cmd_args(start, end);
	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	i = 0;
	while (start && start != end)
	{
		if (is_redir_token(start->type) && start->next != end)
			start = start->next;
		else if (should_keep_word(start))
		{
			argv[i] = ft_strdup(start->value);
			if (!argv[i])
				return (free_argv_partial(argv, i));
			i++;
		}
		start = start->next;
	}
	argv[i] = NULL;
	return (argv);
}

t_cmd	*create_cmd_node(char **argv, t_redir *redirs)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = argv;
	cmd->redirs = redirs;
	cmd->next = NULL;
	return (cmd);
}

t_cmd	*parse_command(t_token *start, t_token *end)
{
	char	**argv;
	t_redir	*redirs;
	t_cmd	*cmd;

	argv = build_cmd_argv(start, end);
	if (!argv)
		return (NULL);
	redirs = parse_redirs(start, end);
	if (!redirs && has_redirection(start, end))
		return (free_argv(argv), NULL);
	cmd = create_cmd_node(argv, redirs);
	if (!cmd)
	{
		free_argv(argv);
		free_redir_list(redirs);
		return (NULL);
	}
	return (cmd);
}