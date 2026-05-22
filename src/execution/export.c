/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassad <mfassad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 17:47:55 by kal-mawl          #+#    #+#             */
/*   Updated: 2026/05/22 19:53:38 by mfassad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../libft/libft.h"

static int	is_valid(char *str)
{
	int	i;

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

static int	env_count(char **envp)
{
	int	count;

	count = 0;
	while (envp && envp[count])
		count++;
	return (count);
}

static int	name_len(char *str)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != '=')
		len++;
	return (len);
}

static int	find_var_index(char *name, char **envp)
{
	int	i;
	int	len;

	if (!name || !envp)
		return (-1);
	len = name_len(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0
			&& (envp[i][len] == '=' || envp[i][len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

static void	update_var(char **envp, int index, char *arg)
{
	free(envp[index]);
	envp[index] = ft_strdup(arg);
}

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