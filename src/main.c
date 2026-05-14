
#include "../include/minishell.h"
#include "../include/execution.h"
#include "../libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

static void	free_envp(char **envp)
{
    int	i;

    if (!envp)
        return ;
    i = 0;
    while (envp[i])
    {
        free(envp[i]);
        i++;
    }
    free(envp);
}

static void	free_shell(t_shell *shell)
{
    if (!shell)
        return ;
    if (shell->envp)
        free_envp(shell->envp);
    free(shell);
}

static char	*build_shlvl_string(int shlvl_val)
{
    char	*num_str;
    char	*result;

    num_str = ft_itoa(shlvl_val);  // "2"
    if (!num_str)
        return (NULL);
    result = ft_strjoin("SHLVL=", num_str);  // "SHLVL=2"
    free(num_str);
    return (result);
}

static char	**dup_envp(char **envp)
{
    int		i;
    char	**new_envp;

    i = 0;
    while (envp[i])
        i++;
    new_envp = malloc(sizeof(char *) * (i + 1));
    if (!new_envp)
        return (NULL);
    i = 0;
    while (envp[i])
    {
        new_envp[i] = ft_strdup(envp[i]);
        if (!new_envp[i])
            return (NULL);
        i++;
    }
    new_envp[i] = NULL;
    return (new_envp);
}

static void	update_shlvl(char **envp)
{
    char	*shlvl_str;
    int		shlvl_val;
    char	*new_shlvl;
    int		i;

    shlvl_str = get_env_valuee("SHLVL", envp);
    if (!shlvl_str)
        shlvl_val = 1;
    else
        shlvl_val = ft_atoi(shlvl_str) + 1;
    new_shlvl = build_shlvl_string(shlvl_val);
    if (!new_shlvl)
        return ;
    i = 0;
    while (envp[i])
    {
        if (ft_strncmp(envp[i], "SHLVL", 5) == 0)
        {
            free(envp[i]);  // Now safe - it's our copy
            envp[i] = new_shlvl;
            return ;
        }
        i++;
    }
    free(new_shlvl);
}

static t_shell	*init_shell(char **envp)
{
    t_shell	*shell;

    shell = malloc(sizeof(t_shell));
    if (!shell)
        return (NULL);
    shell->envp = dup_envp(envp);  // Copy first
    if (!shell->envp)
    {
        free(shell);
        return (NULL);
    }
    update_shlvl(shell->envp);  // Update the copy
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
		printf("minishell: syntax error\n");//mana nerjaa nshufa hay
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

static void	handle_input_loop(t_shell *shell, char *input)
{
    int	signal_status;

    signal_status = get_signal_status();
    if (signal_status)
    {
        shell->last_status = signal_status;
        free(input);
        return ;
    }
    if (input[0])
    {
        add_history(input);
        execute_user_input(shell, input);
    }
    free(input);
}

static int	main_loop(t_shell *shell)
{
    char	*input;

    setup_signals_interactive();
    while (1)
    {
        input = readline("minishell$ ");
        if (!input)
        {
            ft_putstr_fd("exit\n", 1);//jdide
            break ;
        }
        handle_input_loop(shell, input);
        reset_signal_status();
    }
    return (shell->last_status);
}

int	main(int argc, char **argv, char **envp)
{
    t_shell	*shell;
    int		status;

    (void)argc;
    (void)argv;
    shell = init_shell(envp);
    if (!shell)
        return (1);
    status = main_loop(shell);
    free_shell(shell);
    return (status);
}

// Main interactive shell loop with signal handling
// int	main(int argc, char **argv, char **envp)
// {
// 	t_shell	*shell;
// 	char	*input;
// 	int		status;

// 	(void)argc;
// 	(void)argv;
// 	shell = init_shell(envp);
// 	if (!shell)
// 		return (1);
// 	setup_signals_interactive();
// 	while (1)
// 	{
// 		input = readline("minishell$ ");
// 		if (!input)
// 			break ;
// 		if (input[0])
// 		{
// 			add_history(input);
// 			execute_user_input(shell, input);
// 		}
// 		free(input);
// 	}
// 	status = shell->last_status;
// 	free(shell);
// 	return (status);
// }
