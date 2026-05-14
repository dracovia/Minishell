/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kal-mawl <kal-mawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 17:47:18 by kal-mawl          #+#    #+#             */
/*   Updated: 2026/05/13 17:47:19 by kal-mawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"

static int is_n_flag(char *str)
{
    int i;

    if (!str || str[0] != '-')
        return (0);
    i = 1;
    if (str[i] == '\0')
        return (0);
    while (str[i] == 'n')
        i++;
    if (str[i] != '\0')
        return (0);
    return (1);
}

int builtin_echo(char **argv)
{
    int i;
    int n_flag;

    n_flag = 0;
    i = 1;
    while (argv[i] && is_n_flag(argv[i]))
    {
        n_flag = 1;
        i++;
    }
    while (argv[i])
    {
        write(1, argv[i], ft_strlen(argv[i]));
        if (argv[i + 1])
            write(1, " ", 1);
        i++;
    }
    if (!n_flag)
        write(1, "\n", 1);
    return (0);
}