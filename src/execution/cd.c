#include "../../libft/libft.h"
#include "../../include/minishell.h"
#include <stdio.h>
#include <string.h>

static char *get_env_value(char *key, char **envp)
{
    int     i;
    size_t  key_len;

    if (!key || !envp)
        return (NULL);
    key_len = strlen(key);
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
        path = get_env_value("HOME", shell->envp);
        if (!path)
        {
            printf("cd: HOME not set\n");
            return (1);
        }
    }
    else if (argv[2])
    {
        printf("cd: too many arguments\n");
        return (1);
    }
    else
        path = argv[1];
    if (chdir(path) != 0)
    {
        perror("cd");
        return (1);
    }
    return (0);
}