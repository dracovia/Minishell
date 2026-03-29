/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassad <mfassad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 21:26:35 by mfassad           #+#    #+#             */
/*   Updated: 2026/03/13 17:19:18 by mfassad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	has_unclosed_quotes(char *line);
t_quote_type	update_quote_state(t_quote_type state, char c);
int	is_operator_char(char c);
int	is_quote_char(char c);
int	operator_len(char *line);
char	*ft_strdup(const char *s1);
int	is_space(char c);
char	*join_and_free(char *s1, char *s2);
int	is_var_start(char c);
char	*expand_fail(char *result);
char	**free_argv_partial(char **argv, int used);
int	is_redir_token(t_token_type type);
# endif