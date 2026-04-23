#include "../../include/minishell.h"
#include "../../libft/libft.h"
#include <stdlib.h>

static int	is_numeric(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int builtin_exit(t_shell *shell, char **argv)
{
    long status;

    if (!argv[1])
        exit(shell->last_status);
    if (!is_numeric(argv[1]))
    {
        ft_putstr_fd("exit: numeric argument required\n", 2);
        exit(2);
    }
    if (argv[2])
    {
        ft_putstr_fd("exit: too many arguments\n", 2);
        return (1);   
    }
    status = atol(argv[1]) % 256;
    exit(status);
}