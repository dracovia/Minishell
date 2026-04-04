#include "../../libft/libft.h"
#include "../../include/minishell.h"

char *get_env_valuee(char *key, char **envp)
{
    int     i;
    int  key_len;

    if (!key || !envp)
        return (NULL);
    key_len = ft_strlen(key);
    i = 0;
    while (envp[i])
    {
        if (ft_strncmp(envp[i], key, key_len) == 0 
            && envp[i][key_len] == '=')
            return (envp[i] + key_len + 1);
        i++;
    }
    return (NULL);
}

int builtin_cd(t_shell *shell, char **argv)
{
    char *path;

    if (!argv[1])
    {
        path = get_env_valuee("HOME", shell->envp);
        if (!path)
        {
            ft_putstr_fd("cd: HOME not set\n", 2);
            return (1);
        }
    }
    else if (argv[2])
    {
        ft_putstr_fd("cd: too many arguments\n", 2);
        return (1);
    }
    else
        path = argv[1];
    if (chdir(path) != 0)
        return (perror("cd"), 1);
    return (0);
}