#include "../../include/builtins.h"
#include "../../libft/libft.h"

int is_valid(char *str)
{
    int i;

    if (!str || !str[0] || (str[0] != '-' && !ft_isalpha(str[0])))
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
	envp[index] = strdup(arg);
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
		if (strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
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
	while (envp[i])
	{
		new_env[i] = strdup(envp[i]);
		i++;
	}
	new_env[i] = strdup(arg);
	new_env[i + 1] = NULL;
	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
	return (new_env);
}

int  builtin_export(t_shell *shell, char **argv)
{
    int i;
    int index;

    if (!argv[1])
        return (0);
    i = 1;
    while (argv[i])
    {
        if (!is_valid(argv[i]))
        	printf("export: `%s`: not a valid identifier\n", argv[i]);
        else if (ft_strchr(argv[i], '='))
        {
            index = find_var_index(argv[i], shell -> envp);
            if (index != -1)
                update_var(shell->envp, index, argv[i]);
            else 
                shell->envp = add_var(shell->envp, argv[i]);
        }
        i++;
    }
    return (0);
}