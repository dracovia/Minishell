/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassad <mfassad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 09:09:24 by mfassad           #+#    #+#             */
/*   Updated: 2025/05/29 16:19:55 by mfassad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*p;
	const unsigned char	*s;

	if (dst == NULL && src == NULL)
		return (NULL);
	i = 0;
	p = (unsigned char *) dst;
	s = (const unsigned char *) src;
	while (i < n)
	{
		p[i] = s[i];
		i++;
	}
	return (dst);
}
