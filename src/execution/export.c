/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kal-mawl <kal-mawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 17:47:55 by kal-mawl          #+#    #+#             */
/*   Updated: 2026/05/13 17:47:56 by kal-mawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../libft/libft.h"

int is_valid(char *str)
{
    int i;

    if (!str || !str[0] || (!ft_isalpha(str[0]) && str[0] != '_'))
        return (0);
    i = 1;
    while (str[i] && str[i] != '=')
    {
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

static void	update_var(char **envp, int index, char *arg)
{
	free(envp[index]);
	envp[index] = ft_strdup(arg);
}

static int	find_var_index(char *name, char **envp)
{
	int		i;
	size_t	len;

	if (!name || !envp)
		return (-1);
	len = 0;
	while (name[len] && name[len] != '=')
		len++;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static char	**add_var(char **envp, char *arg)
{
	int		i;
	int		count;
	char	**new_env;

	count = 0;
	while (envp[count])
		count++;
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (envp);
	i = 0;
	while (i < count)
	{
		new_env[i] = envp[i];
		i++;
	}
	new_env[i] = ft_strdup(arg);
	new_env[i + 1] = NULL;
	return (new_env);
}

int	builtin_export(t_shell *shell, char **argv)
{
	int	i;
	int	error;
	error = 0;
	i = 1;
	while (argv[i])
	{
		if (!is_valid(argv[i]))
		{
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			error = 1;
		}
		else if (ft_strchr(argv[i], '='))
		{
			if (find_var_index(argv[i], shell->envp) != -1)
				update_var(shell->envp, find_var_index(argv[i], shell->envp),
					argv[i]);
			else
				shell->envp = add_var(shell->envp, argv[i]);
		}
		i++;
	}
	return (error);
}