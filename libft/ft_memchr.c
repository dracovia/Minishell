/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassad <mfassad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 09:05:21 by mfassad           #+#    #+#             */
/*   Updated: 2025/05/29 16:19:22 by mfassad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t					i;
	const unsigned char		*s2;
	unsigned char			c2;

	i = 0;
	s2 = (const unsigned char *)s;
	c2 = (unsigned char )c;
	while (i < n)
	{
		if (s2[i] == c2)
		{
			return ((void *)&s2[i]);
		}
		i++;
	}
	return (NULL);
}
