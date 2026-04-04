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