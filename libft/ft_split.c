/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassad <mfassad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 11:43:02 by mfassad           #+#    #+#             */
/*   Updated: 2025/05/29 16:25:39 by mfassad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t	word_count(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

static char	*next_word(const char *s, char c, size_t *len)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	*len = i;
	return (ft_substr(s, 0, i));
}

char	**ft_split(char const *s, char c)
{
	size_t		i;
	size_t		len;
	char		**arr;

	if (!s)
		return (NULL);
	arr = (char **)malloc((word_count(s, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			arr[i] = next_word(s, c, &len);
			if (!arr[i++])
				return (NULL);
			s += len;
		}
	}
	arr[i] = NULL;
	return (arr);
}
