/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kal-mawl <kal-mawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 17:48:44 by kal-mawl          #+#    #+#             */
/*   Updated: 2026/05/13 17:48:45 by kal-mawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../libft/libft.h"

static int	find_var_index(char *name, char **envp)
{
	int		i;
	size_t	len;

	if (!name || !envp)
		return (-1);
	len = strlen(name);
	i = 0;
	while (envp[i])
	{
		if (strncmp(envp[i], name, len) == 0
			&& envp[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static void	free_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}


static char	**copy_env_without_unset(char **envp, int index)
{
	int		i;
	int		j;
	int		count;
	char	**new_env;

	count = -1;
	while (envp[++count])
		;
	new_env = malloc(sizeof(char *) * count);
	if (!new_env)
		return (NULL);
	i = -1;
	j = 0;
	while (envp[++i])
	{
		if (i != index)
		{
			new_env[j++] = ft_strdup(envp[i]);
			if (!new_env[j - 1])
				return (new_env[--j] = NULL, free_env(new_env), NULL);
		}
	}
	new_env[j] = NULL;
	return (new_env);
}

static char	**remove_var(char **envp, int index)
{
	char	**new_env;

	new_env = copy_env_without_unset(envp, index);
	if (!new_env)
		return (envp);
	return (new_env);
}

int	builtin_unset(t_shell *shell, char **argv)
{
	int	i;
	int	index;

	if (!argv[1])
		return (0);
	i = 1;
	while (argv[i])
	{
		index = find_var_index(argv[i], shell->envp);
		if (index != -1)
			shell->envp = remove_var(shell->envp, index);
		i++;
	}
	return (0);
}