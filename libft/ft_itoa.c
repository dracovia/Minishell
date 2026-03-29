/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassad <mfassad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:46:35 by mfassad           #+#    #+#             */
/*   Updated: 2025/05/29 16:46:32 by mfassad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static	int	length_num(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char		*res;
	int			len;
	long long	num;

	len = length_num(n);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	res[len--] = '\0';
	num = (long)n;
	if (n == 0)
		res[0] = '0';
	if (num < 0)
	{
		num *= -1;
		res[0] = '-';
	}
	while (num > 0)
	{
		res[len--] = (num % 10) + '0';
		num /= 10;
	}
	return (res);
}
