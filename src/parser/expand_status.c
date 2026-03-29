/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassad <mfassad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 21:27:06 by mfassad           #+#    #+#             */
/*   Updated: 2026/03/13 00:52:33 by mfassad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//$? is a special expansion case

#include "../../include/minishell.h"

char	*status_to_str(int status)
{
    return ft_itoa(status);
}

int	expand_status(char *str, int *i, char **result, int last_status)
{
	char	*status;
	char	*joined;

	(void)str;
	status = status_to_str(last_status);
	if (!status)
		return (0);
	joined = join_and_free(*result, status);
	if (!joined)
		return (0);
	*result = joined;
	*i += 2;
	return (1);
}
