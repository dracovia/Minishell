/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kal-mawl <kal-mawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 17:47:55 by kal-mawl          #+#    #+#             */
/*   Updated: 2026/06/19 15:57:08 by kal-mawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../libft/libft.h"

static char	**add_var(char **envp, char *arg)
{
	int		i;
	int		count;
	char	**new_env;

	count = env_count(envp);
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
	free(envp);
	return (new_env);
}

static void	print_export_line(char *env)
{
	int	i;

	i = 0;
	ft_putstr_fd("declare -x ", 1);
	while (env[i] && env[i] != '=')
	{
		ft_putchar_fd(env[i], 1);
		i++;
	}
	if (env[i] == '=')
	{
		ft_putstr_fd("=\"", 1);
		i++;
		while (env[i])
		{
			ft_putchar_fd(env[i], 1);
			i++;
		}
		ft_putchar_fd('"', 1);
	}
	ft_putchar_fd('\n', 1);
}

static void	print_export(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		print_export_line(envp[i]);
		i++;
	}
}

static int	handle_export_arg(t_shell *shell, char *arg)
{
	int	index;

	if (!is_valid(arg))
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	index = find_var_index(arg, shell->envp);
	if (index != -1)
	{
		if (ft_strchr(arg, '='))
			update_var(shell->envp, index, arg);
	}
	else
		shell->envp = add_var(shell->envp, arg);
	return (0);
}

int	builtin_export(t_shell *shell, char **argv)
{
	int	i;
	int	error;

	if (!argv[1])
	{
		print_export(shell->envp);
		return (0);
	}
	error = 0;
	i = 1;
	while (argv[i])
	{
		if (handle_export_arg(shell, argv[i]))
			error = 1;
		i++;
	}
	return (error);
}
