/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kal-mawl <kal-mawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 17:48:24 by kal-mawl          #+#    #+#             */
/*   Updated: 2026/05/13 17:48:25 by kal-mawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"

int builtin_pwd(void)
{
    char *pwd;

    pwd = getcwd(NULL, 0);
    if (!pwd)
    {
        perror("pwd");
        return (1);
    }
    ft_putstr_fd(pwd, 1);
    ft_putchar_fd('\n', 1);
    free(pwd);
    return (0);
}