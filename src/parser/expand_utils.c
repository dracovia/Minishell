/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassad <mfassad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 21:27:09 by mfassad           #+#    #+#             */
/*   Updated: 2026/03/13 00:19:53 by mfassad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

// is this a valid variable-name start?
// is this a valid variable-name character?
// how long is the variable name after $?
// what is the value of this variable in envp?
// how do I safely append strings while building expanded output?

#include "../../include/minishell.h"

int	is_var_start(char c)
{
	return (ft_isalpha(c) || c == '_');
}

int	is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	var_name_len(char *str)
{
	int	len;

	len = 0;
	if (!str || !is_var_start(str[0]))
		return (0);
	while (str[len] && is_var_char(str[len]))
		len++;
	return (len);
}

char	*get_env_value(char *name, char **envp)
{
	int		i;
	int		len;

	if (!name || !envp)
		return (ft_strdup(""));
	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], name, len) && envp[i][len] == '=')
			return (ft_strdup(envp[i] + len + 1));
		i++;
	}
	return (ft_strdup(""));
}

char	*join_and_free(char *s1, char *s2)
{
	char	*joined;

	joined = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (joined);
}