/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassad <mfassad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 21:26:44 by mfassad           #+#    #+#             */
/*   Updated: 2026/06/17 23:34:03 by mfassad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_HEREDOC,
	T_APPEND
}	t_token_type;

typedef enum e_quote_type
{
	Q_NONE,
	Q_SINGLE,
	Q_DOUBLE
}	t_quote_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	t_quote_type	quote;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	t_token_type	type;
	char			*target;
	t_quote_type	quote;
	int				fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**argv;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_parser
{
	char	*line;
	t_token	*tokens;
	t_cmd	*cmds;
	char	**envp;
	int		last_status;
}	t_parser;

int				is_in_quotes(t_quote_type state);
int				is_quote_char(char c);
t_quote_type	update_quote_state(t_quote_type state, char c);
int				has_unclosed_quotes(char *line);

int				is_operator_char(char c);
int				operator_len(char *line);
int				has_next_word(char *line, int i);
int				prev_non_space_index(char *line, int i);

int				has_invalid_operators(char *line);

int				is_space(char c);
int				skip_spaces(char *line, int i);
int				handle_token(char *line, int *i, t_token **tokens);
t_token			*lexer(char *line);

t_token_type	get_operator_type(char *line);
char			*get_operator_value(char *line);
t_token			*create_operator_token(char *line);
int				handle_operator_token(char *line, int *i, t_token **tokens);

int				word_len(char *line, int i);
char			*extract_word(char *line, int *i);
t_quote_type	get_word_quote_type(char *word);
t_token			*create_word_token(char *line, int *i);
int				handle_word_token(char *line, int *i, t_token **tokens);

t_token			*new_token(char *value, t_token_type type,
					t_quote_type quote);
t_token			*last_token(t_token *tokens);
int				append_token(t_token **tokens, t_token *new_token);
int				token_count(t_token *tokens);
void			free_token_list(t_token *tokens);

int				is_var_start(char c);
int				is_var_char(char c);
int				var_name_len(char *str);
char			*get_env_value(char *name, char **envp);
char			*join_and_free(char *s1, char *s2);
char			*expand_fail(char *result);

char			*status_to_str(int status);
int				expand_status(char *str, int *i,
					char **result, int last_status);

int				should_expand_var(char *str, int i,
					t_quote_type quote);
int				copy_normal_char(char *str, int *i,
					char **result, t_quote_type *quote);
int				expand_variable(char *str, int *i,
					char **result, char **envp);
char			*expand_token_value(char *value,
					char **envp, int last_status);
int				expand_tokens(t_token *tokens,
					char **envp, int last_status);

t_token			*next_pipe_token(t_token *tokens);
t_token			*token_after_pipe(t_token *tokens);
int				append_cmd(t_cmd **cmds, t_cmd *new_cmd);
t_cmd			*parse_pipeline_segment(t_token *start, t_token *end);
t_cmd			*parse_pipeline(t_token *tokens);

int				count_cmd_args(t_token *start, t_token *end);
char			**build_cmd_argv(t_token *start, t_token *end);
t_cmd			*create_cmd_node(char **argv, t_redir *redirs);
t_cmd			*parse_command(t_token *start, t_token *end);

t_redir			*create_redir_node(t_token *op_token,
					t_token *target_token);
t_redir			*parse_redirs(t_token *start, t_token *end);

void			free_argv(char **argv);
char			**free_argv_partial(char **argv, int used);
t_cmd			*last_cmd(t_cmd *cmds);
void			free_cmd_list(t_cmd *cmds);
int				has_redirection(t_token *start, t_token *end);

int				is_redir_token(t_token_type type);
t_redir			*new_redir(char *target, t_token_type type,
					t_quote_type quote);
t_redir			*last_redir(t_redir *redirs);
int				append_redir(t_redir **redirs, t_redir *new_redir);
void			free_redir_list(t_redir *redirs);

int				validate_input(char *line);
t_token			*build_token_list(char *line,
					char **envp, int last_status);
t_cmd			*build_command_list(t_token *tokens);
t_parser		*parse_input(char *line,
					char **envp, int last_status);
void			free_parser(t_parser *parser);
void			free_parser_keep_cmds(t_parser *parser);

void			free_tokens_and_cmds(t_token *tokens, t_cmd *cmds);
void			free_tokens_and_redirs(t_token *tokens, t_redir *redirs);
void			free_parser_data(t_token *tokens,
					t_cmd *cmds, t_redir *redirs);
char			**cleanup_argv_and_return_null(char **argv);
t_cmd			*cleanup_tokens_and_return_null(t_token *tokens);

char			*token_type_str(t_token_type type);
void			print_token_list(t_token *tokens);
void			print_argv(char **argv);
void			print_redir_list(t_redir *redirs);
void			print_cmd_list(t_cmd *cmds);

int				count_unquoted_len(char *str);
char			*remove_quotes_from_value(char *str);
int				remove_quotes_from_tokens(t_token *tokens);

int				has_next_command_part(char *line, int i);
int				should_expand_var(char *str, int i, t_quote_type quote);
int				validate_input(char *line);

#endif