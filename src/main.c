
#include "../include/minishell.h"
#include "../include/execution.h"
#include <readline/readline.h>
#include <readline/history.h>

// Initialize shell structure with environment and default values
static t_shell	*init_shell(char **envp)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->envp = envp;
	shell->last_status = 0;
	shell->cmds = NULL;
	return (shell);
}

// Execute a single user input and update shell status
static void	execute_user_input(t_shell *shell, char *input)
{
	t_parser	*parser;

	parser = parse_input(input, shell->envp, shell->last_status);
	if (!parser)
	{
		printf("minishell: syntax error\n");
		return ;
	}
	if (!parser->cmds)
	{
		free_parser_keep_cmds(parser);
		return ;
	}
	shell->last_status = execute_commands(shell, parser->cmds);
	free_parser(parser);
}

// Main interactive shell loop with signal handling
int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	char	*input;
	int		status;

	(void)argc;
	(void)argv;
	shell = init_shell(envp);
	if (!shell)
		return (1);
	setup_signals_interactive();
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (input[0])
		{
			add_history(input);
			execute_user_input(shell, input);
		}
		free(input);
	}
	status = shell->last_status;
	free(shell);
	return (status);
}