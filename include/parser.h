/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassad <mfassad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 21:26:44 by mfassad           #+#    #+#             */
/*   Updated: 2026/03/13 17:21:30 by mfassad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

// What kind of thing did I just read from the input? (done by tokenizer)
typedef enum e_token_type
{
	T_WORD,		 // Used for normal command text (ls , -l , hello, etc.)
	T_PIPE,		 // Used for the | character, which connects two commands together.
	T_REDIR_IN,	 // Used to know that the next token must be a file and this file is input redirection target <
	T_REDIR_OUT, // Used to mark normal output redirection >
	T_HEREDOC,	 // used to mark a heredoc <<, which tells that next token is not a normal filename but a delimiter for the heredoc content
	T_APPEND	 // used to mark append output redirection >>, which tells that the next token is a file and this file is output redirection target, but instead of overwriting the file, it appends to it.
} t_token_type;

typedef enum e_quote_type
{
	Q_NONE,	  // Normal mode i.e spaces split the words/ tokens , |, <, >, <<, >> are operators and $VAR can expand.
	Q_SINGLE, // prevent interpretation of metacharacters i.e Everything becomes literal until the closing 'and $ expansion is also prevented in single quotes.
	Q_DOUBLE  // Still protects spaces and operators from splitting the token, but still allows $ expansion.
} t_quote_type;
// this enables lexer to read raw text and produce a linked list of tokens, each token has a type (word, pipe, redirection, etc.) and a value (the actual text of the token).
typedef struct s_token
{
	char *value; // The actual text of the token, e.g "ls", "-l", "|", ">", etc.
	t_token_type type;
	t_quote_type quote;	  // Did this token come from a quoted context? (usefull for empty tokens and for knowing if $ expansion should be done or not)
	struct s_token *next; // Because token count is unknown at first, and appending tokens during lexing is natural
} t_token;
// this represents one redirection attached to one command.
typedef struct s_redir
{
	t_token_type type; // It has a type (input, output, heredoc, append)
	char *target;	   //  a target (the file name or heredoc delimiter)and  this target should be open for writing , reading , appending  or has heredoc content?
	t_quote_type quote;
	struct s_redir *next; //  a pointer to the next redirection in the same command (since a command can have multiple redirections).
} t_redir;
// this represents one command in the pipeline.
typedef struct s_cmd
{
	char **argv;		// build from tokens of type T_WORD .(argv = ["echo", "hello", NULL])
	t_redir *redirs;	// stores all redirections belonging to this command. eg grep x < in.txt > out.txt here grep is cmd
	struct s_cmd *next; // grep x < in.txt > out.txt ,eg ls | grep c | wc (each is node in list of cmds)
} t_cmd;

typedef struct s_parser
{
	char *line;		 // raw input from readline
	t_token *tokens; // token list produced after lexing
	t_cmd *cmds;	 // final parsed command list
	char **envp;	 // environment variables, needed for $ expansion and for execve
	int last_status; // This stores the previous command exit status (used to handle $?))
} t_parser;

#endif