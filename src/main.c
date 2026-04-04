
#include "../include/minishell.h"

static void	test_one_input(char *input, char **envp, int last_status)
{
	t_cmd	*cmds;

	printf("========================================\n");
	printf("INPUT: %s\n", input);
	cmds = parse_input(input, envp, last_status);
	if (!cmds)
	{
		printf("Parse failed or input invalid.\n");
		return ;
	}
	print_cmd_list(cmds);
	free_cmd_list(cmds);
}

int	main(int argc, char **argv, char **envp)
{
	char	*tests[] = {
		"echo ab\"cd\"ef",
		"echo ab'$USER'ef",
		"echo \"a|b\"",
		"echo \"a>b\"",
		"echo '$?'",
		"echo $NOTFOUND",
		"echo \"$NOTFOUND\"",
		"echo $",
		"echo $5",
		"echo \"$\"",
		"echo \"\"",
		"echo ''",
		"cat < \"in file.txt\"",
		"echo hi > \"out file.txt\"",
		NULL
	};
	int		i;

	(void)argc;
	(void)argv;
	i = 0;
	while (tests[i])
	{
		test_one_input(tests[i], envp, 42);
		i++;
	}
	return (0);
}