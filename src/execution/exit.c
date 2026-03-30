#include "../../include/builtins.h"
#include "../../include/minishell.h"
#include <stdio.h>
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

    printf("exit\n");
    if (!argv[1])
        exit(shell->last_status);
    if (!is_numeric(argv[1]))
    {
        printf("exit: numeric argument required\n");
        exit(255); //we use 255 as a strong error signal
    }
    if (argv[2])
    {
        printf("exit: too many arguments\n");
        return (1);   
    }
    status = atol(argv[1]) % 256;
    exit(status);
}