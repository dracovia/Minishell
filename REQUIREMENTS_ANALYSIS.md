# MINISHELL REQUIREMENTS ANALYSIS

## Project Requirements (from Subject)

### 1. QUOTE HANDLING
- **Single Quotes (')**: Prevent the shell from interpreting metacharacters
  - ✓ Implemented in: `src/parser/syntax_quotes.c`
  - ✓ Parser header: `t_quote_type Q_SINGLE` in parser.h
  - ✓ Quote validation: `has_unclosed_quotes()` in syntax_quotes.c
  
- **Double Quotes (")**: Prevent metacharacters EXCEPT $ (dollar sign)
  - ✓ Implemented in: `src/parser/syntax_quotes.c`
  - ✓ Parser header: `t_quote_type Q_DOUBLE` in parser.h
  - ✓ Variable expansion in double quotes handled in expansion logic

- **Unclosed Quotes Error**: Return error if quotes not closed
  - ✓ Function exists: `has_unclosed_quotes()` in syntax_quotes.c
  - ✓ Validated in: `validate_input()` in parser_entry.c

### 2. REDIRECTIONS
- **< (Input Redirection)**: Redirect input from file
  - ✓ Token type defined: `T_REDIR_IN` in parser.h
  - ✓ Lexer recognizes: `get_operator_type()` in lexer_operators.c
  - ✓ Parser handles: `parse_redirs()` in parse_redirs.c
  - ✓ Execution: `redirection()` function in redir.c
  
- **> (Output Redirection)**: Redirect output to file
  - ✓ Token type defined: `T_REDIR_OUT` in parser.h
  - ✓ Lexer recognizes: `get_operator_type()` in lexer_operators.c
  - ✓ Parser handles: `parse_redirs()` in parse_redirs.c
  - ✓ Execution: `redirection()` function in redir.c
  
- **<< (Heredoc)**: Read input until delimiter found
  - ✓ Token type defined: `T_HEREDOC` in parser.h
  - ✓ Lexer recognizes: `get_operator_type()` in lexer_operators.c
  - ✓ Handler: `handle_heredoc()` in heredoc.c
  - ✓ Function reads until delimiter, supports variable expansion
  
- **>> (Append)**: Redirect output in append mode
  - ✓ Token type defined: `T_APPEND` in parser.h
  - ✓ Lexer recognizes: `get_operator_type()` in lexer_operators.c
  - ✓ Parser handles: `parse_redirs()` in parse_redirs.c
  - ✓ Execution: `redirection()` function in redir.c

### 3. PIPES
- **| (Pipe Operator)**: Connect output of one command to input of next
  - ✓ Token type defined: `T_PIPE` in parser.h
  - ✓ Lexer recognizes: `get_operator_type()` in lexer_operators.c
  - ✓ Parser handles: `parse_pipeline()` in parse_pipeline.c
  - ✓ Execution: `execute_pipeline()` in execute_pipeline.c
  - ✓ Child process setup: `pipeline_child()` in pipeline_child.c
  - ✓ Creates pipe(), fork(), connects fds with `setup_child_fds()`

### 4. VARIABLE EXPANSION
- **$VAR (Environment Variables)**: Expand to environment value
  - ✓ Expansion logic: `expand_variable()` in expand_core.c
  - ✓ Helper functions: `get_env_value()` in expand_utils.c
  - ✓ Variable detection: `is_var_start()`, `var_name_len()` in expand_utils.c
  - ✓ Respects quote context: Expands in Q_NONE and Q_DOUBLE, NOT in Q_SINGLE
  
- **$? (Exit Status)**: Expand to last exit status
  - ✓ Expansion logic: `expand_status()` in expand_status.c
  - ✓ Conversion: `status_to_str()` in expand_status.c
  - ✓ Status tracking: `shell->last_status` in minishell.h
  - ✓ Updated in: `execute_user_input()` in main.c

### 5. SIGNAL HANDLING (Interactive Mode)
- **Ctrl+C**: Display new prompt on new line
  - ✓ Handler: `handle_sigint()` in signals.c
  - ✓ Uses: `rl_on_new_line()` and `rl_redisplay()` (readline)
  - ✓ Setup: `setup_signals_interactive()` in signals.c
  - ✓ Called in: main() at program start

- **Ctrl+D**: Exit the shell
  - ✓ readline() returns NULL on Ctrl+D
  - ✓ Handled in: main.c `while(1) { input = readline(...) if (!input) break; }`

- **Ctrl+\\** : Do nothing
  - ✓ Setup: `signal(SIGQUIT, SIG_IGN)` in setup_signals_interactive()

### 6. BUILT-IN COMMANDS

- **echo [-n]**: Print arguments
  - ✓ Function: `builtin_echo()` in echo.c
  - ✓ Handles -n option: Prevents newline
  - ✓ Registered: `is_builtin()` checks for "echo"
  - ✓ Executed: `exec_builtin()` dispatches to builtin_echo()

- **cd [path]**: Change directory
  - ✓ Function: `builtin_cd()` in cd.c
  - ✓ Accepts relative/absolute paths
  - ✓ Updates PWD environment variable
  - ✓ Registered: `is_builtin()` checks for "cd"
  - ✓ Executed: `exec_builtin()` dispatches to builtin_cd()

- **pwd**: Print working directory
  - ✓ Function: `builtin_pwd()` in pwd.c
  - ✓ No options
  - ✓ Registered: `is_builtin()` checks for "pwd"
  - ✓ Executed: `exec_builtin()` dispatches to builtin_pwd()

- **export [name=value]**: Set environment variables
  - ✓ Function: `builtin_export()` in export.c
  - ✓ No options (only name=value format)
  - ✓ Modifies shell->envp
  - ✓ Registered: `is_builtin()` checks for "export"
  - ✓ Executed: `exec_builtin()` dispatches to builtin_export()

- **unset [name]**: Unset environment variables
  - ✓ Function: `builtin_unset()` in unset.c
  - ✓ No options
  - ✓ Removes from shell->envp
  - ✓ Registered: `is_builtin()` checks for "unset"
  - ✓ Executed: `exec_builtin()` dispatches to builtin_unset()

- **env**: Print environment
  - ✓ Function: `builtin_env()` in env.c
  - ✓ No options or arguments
  - ✓ Prints all envp entries
  - ✓ Registered: `is_builtin()` checks for "env"
  - ✓ Executed: `exec_builtin()` dispatches to builtin_env()

- **exit [status]**: Exit the shell
  - ✓ Function: `builtin_exit()` in exit.c
  - ✓ No options
  - ✓ Returns exit status
  - ✓ Registered: `is_builtin()` checks for "exit"
  - ✓ Executed: `exec_builtin()` dispatches to builtin_exit()

---

## ARCHITECTURE OVERVIEW

### Parser Flow
1. **Input Validation** (`validate_input()` in parser_entry.c)
   - Check for unclosed quotes
   - Check for invalid operators

2. **Tokenization** (`lexer()` in lexer_core.c)
   - Converts raw input to token list
   - Handles operators and words

3. **Expansion** (`expand_tokens()` in expand_core.c)
   - Expands environment variables
   - Expands $? status variable
   - Respects quote context

4. **Quote Removal** (`remove_quotes_from_tokens()` in quote_removal.c)
   - Removes quote characters from token values
   - Preserves token classification

5. **Parsing** (`parse_pipeline()` in parse_pipeline.c)
   - Converts token list to command list
   - Handles pipes and redirections
   - Builds t_cmd structures

### Execution Flow
1. **Entry Point** (`main()` in main.c)
   - Initializes shell structure
   - Sets up signal handlers
   - Reads user input with readline()

2. **Command Execution** (`execute_user_input()` in main.c)
   - Parses input using parse_input()
   - Executes via execute_commands()
   - Updates shell->last_status

3. **Execution Strategy** (`execute_commands()` in execute_commands.c)
   - Routes to execute_pipeline() if multiple commands
   - Routes to execute_single() if single command

4. **Pipeline Execution** (`execute_pipeline()` in execute_pipeline.c)
   - Creates pipes between commands
   - Forks child processes
   - Sets up file descriptors

5. **Single Command** (`execute_single()` in execute_single.c)
   - Checks if builtin or external
   - Handles redirections
   - Executes via execve() or builtin function

---

## DATA STRUCTURES

### t_parser (parser.h)
- Contains: line, tokens, cmds, envp, last_status
- Used for complete input processing

### t_shell (minishell.h)
- Contains: envp, last_status, cmds
- Used for execution

### t_token (parser.h)
- Contains: value, type, quote, next
- Linked list of tokens

### t_cmd (parser.h)
- Contains: argv, redirs, next
- Represents a command (possibly in pipeline)

### t_redir (parser.h)
- Contains: type, target, quote, next
- Represents a redirection

---

## COMPILATION & TESTING

### Build Command
```bash
make clean && make
```

### Run Interactive Shell
```bash
./minishell
minishell$ echo hello
minishell$ exit
```

### Test Commands
See `test_requirements.sh` for comprehensive test cases.

---

## MISSING OR INCOMPLETE FEATURES

Based on requirement analysis, the implementation appears COMPLETE for all stated requirements.

Note: Some features like `history` (readline) are automatically provided by the readline library.

---

## STATUS SUMMARY

- ✓ Quote handling (single & double)
- ✓ Redirections (< > >> <<)
- ✓ Pipes (|)
- ✓ Variable expansion ($VAR, $?)
- ✓ Signal handling (Ctrl+C, Ctrl+D, Ctrl+\\)
- ✓ All 7 built-in commands (echo, cd, pwd, export, unset, env, exit)
- ✓ Interactive prompt with history
- ✓ Parser → Execution integration

